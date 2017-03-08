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
                    Enum[e.Name] = e;
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
        public List<string> Dependency = new List<string>();
    }

    public class GameEnum
    {
        public string Name;
        public Dictionary<string, int> Value = new Dictionary<string, int>();
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

        public string FormatMapping(Case memberCase, string dataVariable, string gameSetupVariable, string gameStateVariable, string memberAccess = ".", string startIndex = "[", string endIndex = "]")
        {
            StringBuilder str = new StringBuilder();
            FormatMapping(memberCase, dataVariable, gameSetupVariable, gameStateVariable, memberAccess, startIndex, endIndex, str);
            return str.ToString();
        }

        public void FormatMapping(Case memberCase, string dataVariable, string gameSetupVariable, string gameStateVariable, string memberAccess, string startIndex, string endIndex, StringBuilder str)
        {
            switch (Source)
            {
                case IndexSource.Data:
                    str.Append(dataVariable);
                    break;
                case IndexSource.GameSetup:
                    str.Append(gameSetupVariable);
                    break;
                case IndexSource.GameState:
                    str.Append(gameStateVariable);
                    break;
                default:
                    throw new Exception("Unknown source");
            }
            foreach (IndexMappingMember member in Member)
            {
                str.Append(memberAccess);
                member.FormatMapping(memberCase, dataVariable, gameSetupVariable, gameStateVariable, memberAccess, startIndex, endIndex, str);
            }
        }
    }

    public class IndexMappingMember
    {
        public string Name;
        public IndexMapping Index = null;
        public void FormatMapping(Case memberCase, string dataVariable, string gameSetupVariable, string gameStateVariable, string memberAccess, string startIndex, string endIndex, StringBuilder str)
        {
            str.Append(memberCase.Convert(Name));
            if (Index != null)
            {
                str.Append(startIndex);
                Index.FormatMapping(memberCase, dataVariable, gameSetupVariable, gameStateVariable, memberAccess, startIndex, endIndex, str);
                str.Append(endIndex);
            }
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
