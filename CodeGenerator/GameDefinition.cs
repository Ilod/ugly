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
                        if (m.Id)
                        {
                            c.IdMember = m;
                            break;
                        }
                        if (m.Condition != null)
                            conditions.Add(new KeyValuePair<string, string>(m.Type, m.Condition.Function));
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
        public ClassMember IdMember = null;
    }

    public class ClassMember
    {
        public string Name;
        public string Type;
        public bool Id = false;
        public int Array = 0;
        public Condition Condition;
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
