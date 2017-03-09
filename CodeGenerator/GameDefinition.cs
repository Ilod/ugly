using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ugly.CodeGenerator
{

    public class GameDefinition
    {
        public GameConfig Config;
        public List<GameFile> Files = new List<GameFile>();
        public Dictionary<string, GameClass> Class = new Dictionary<string, GameClass>();
        public Dictionary<string, GameEnum> Enum = new Dictionary<string, GameEnum>();
        public List<ClassMethod> Method = new List<ClassMethod>();

        public void ParseTypes()
        {
            Method.Clear();
            Dictionary<int, List<ClassMethod>> methods = new Dictionary<int, List<ClassMethod>>();
            List<KeyValuePair<string, string>> conditions = new List<KeyValuePair<string, string>>();
            foreach (GameFile file in Files)
            {
                foreach (GameClass c in file.Class)
                {
                    Class[c.Name] = c;
                    c.File = file;
                    foreach (ClassMethod m in c.Method)
                    {
                        if (!methods.ContainsKey(m.ApiVersion))
                            methods[m.ApiVersion] = new List<ClassMethod>();
                        methods[m.ApiVersion].Add(m);
                    }
                    foreach (ClassMember m in c.Member)
                    {
                        if (m.Condition != null)
                            conditions.Add(new KeyValuePair<string, string>(m.Type, m.Condition.Function));
                        c.MemberMap[m.Name] = m;
                    }
                }
                foreach (GameEnum e in file.Enum)
                {
                    Enum[e.Name] = e;
                    e.File = file;
                }
            }
            foreach (KeyValuePair<string, string> condition in conditions)
            {
                Class[condition.Key].ConditionMethod.Add(condition.Value);
            }
            foreach (ClassMethod m in methods.Values.SelectMany(l => l))
            {
                m.MethodId = Method.Count;
                Method.Add(m);
            }
        }

        public BasicType GetBasicType(string name)
        {
            switch (name)
            {
                case "uint8":
                    return BasicType.U8;
                case "uint16":
                    return BasicType.U16;
                case "uint32":
                    return BasicType.U32;
                case "uint64":
                    return BasicType.U64;
                case "int8":
                    return BasicType.I8;
                case "int16":
                    return BasicType.I16;
                case "int32":
                    return BasicType.I32;
                case "int64":
                    return BasicType.I64;
                case "char":
                    return BasicType.Char;
                case "bool":
                    return BasicType.Bool;
                default:
                    if (Class.ContainsKey(name))
                        return BasicType.Class;
                    if (Enum.ContainsKey(name))
                        return BasicType.Enum;
                    return BasicType.Void;
            }
        }
    }

    public class GameConfig
    {
        public string Namespace;
        public string GameSetup;
        public string PlayerSetup;
        public string GameState;
        public string PlayerState;
        public string GameServer;
    }

    public class GameFile
    {
        public string Name;
        public List<GameClass> Class = new List<GameClass>();
        public List<GameEnum> Enum = new List<GameEnum>();
    }

    public class GameEnum
    {
        public string Name;
        public Dictionary<string, int> Value = new Dictionary<string, int>();
        [NonSerialized]
        public GameFile File;
    }

    public class GameClass
    {
        public string Name;
        public List<ClassMember> Member = new List<ClassMember>();
        public List<ClassMethod> Method = new List<ClassMethod>();
        public SortedSet<string> ConditionMethod = new SortedSet<string>();
        public GameClassIdConfig Id = null;
        public List<IndexMapping> IndexMapping = new List<IndexMapping>();
        public bool HasId { get { return Id != null && Id.Member.Any(); } }
        [NonSerialized]
        public Dictionary<string, ClassMember> MemberMap = new Dictionary<string, ClassMember>();
        [NonSerialized]
        public GameFile File;
    }

    public class GameClassIdConfig
    {
        public List<string> Member = new List<string>();
        public bool Index = false;
        public IndexMapping Source;
    }

    public enum IndexSource
    {
        Unknown,
        Data,
        GameSetup,
        GameState,
        Index,
    }

    public enum ClassMemberIndexType
    {
        None,
        RefId,
        MappedFromStrong,
        Strong,
    }

    public class ClassMember
    {
        public string Name;
        public string Type;
        public int Array = 0;
        public ClassMemberIndexType Index = ClassMemberIndexType.None;
        public Condition Condition;

        public bool IsWeak { get { return Index == ClassMemberIndexType.RefId || Index == ClassMemberIndexType.MappedFromStrong; } }
    }

    public class IndexMapping
    {
        public IndexSource Source = IndexSource.Unknown;
        public List<IndexMappingMember> Member = new List<IndexMappingMember>();

        public string FormatMapping(Case memberCase, string dataVariable, string gameSetupVariable, string gameStateVariable, string indexSeparator = "][", string memberAccess = ".", string startIndex = "[", string endIndex = "]")
        {
            string source;
            switch (Source)
            {
                case IndexSource.Data:
                    source = dataVariable;
                    break;
                case IndexSource.GameSetup:
                    source = gameSetupVariable;
                    break;
                case IndexSource.GameState:
                    source = gameStateVariable;
                    break;
                default:
                    throw new Exception("Unknown source");
            }
            return string.Join(memberAccess, Enumerable.Repeat(source, 1).Concat(Member.Select(m => m.FormatMapping(memberCase, dataVariable, gameSetupVariable, gameStateVariable, indexSeparator, memberAccess, startIndex, endIndex))));
        }

        public ClassMember GetMember(GameDefinition definition, string data = null)
        {
            GameClass currentClass = null;
            switch (Source)
            {
                case IndexSource.Data:
                    currentClass = definition.Class[data];
                    break;
                case IndexSource.GameSetup:
                    currentClass = definition.Class[definition.Config.GameSetup];
                    break;
                case IndexSource.GameState:
                    currentClass = definition.Class[definition.Config.GameState];
                    break;
                default:
                    throw new Exception("Unknown source");
            }
            ClassMember member = null;
            foreach (string memberName in Member.Select(m => m.Name))
            {
                member = currentClass.MemberMap[memberName];
                currentClass = (definition.GetBasicType(member.Type) == BasicType.Class) ? definition.Class[member.Type] : null;
            }
            return member;
        }
    }

    public class IndexMappingMember
    {
        public string Name;
        public List<IndexMapping> Index = new List<IndexMapping>();
        public string FormatMapping(Case memberCase, string dataVariable, string gameSetupVariable, string gameStateVariable, string indexSeparator, string memberAccess, string startIndex, string endIndex)
        {
            string name = memberCase.Convert(Name);
            if (!Index.Any())
                return name;
            return string.Format("{0}{1}{3}{2}", name, startIndex, endIndex, string.Join(indexSeparator, Index.Select(idx => idx.FormatMapping(memberCase, dataVariable, gameSetupVariable, gameStateVariable, indexSeparator, memberAccess, startIndex, endIndex))));
        }
    }

    public class ClassMethod
    {
        public string Name;
        public List<MethodParam> Param = new List<MethodParam>();
        public int ApiVersion;
        [NonSerialized]
        public int MethodId = -1;
    }

    public class MethodParam
    {
        public string Name;
        public string Type;
    }

    public class Condition
    {
        public string Function;
        public ConditionType Type = ConditionType.When;
    }

    public enum ConditionType
    {
        When,
        While,
    }

    public enum BasicType
    {
        U8,
        U16,
        U32,
        U64,
        I8,
        I16,
        I32,
        I64,
        Char,
        Bool,
        Class,
        Enum,
        Void,
    }
}
