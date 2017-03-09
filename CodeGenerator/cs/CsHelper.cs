using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ugly.CodeGenerator.cs
{
    public static class CsHelper
    {
        public static GameDefinition Definition { get; private set; }
        public static GameFile CurrentFile { get; private set; }
        public static void GenerateFiles(string path, GameDefinition gameDef)
        {
            Definition = gameDef;
            Directory.CreateDirectory(path);
            Generator.WriteFile(Path.Combine(path, "Client.cs"), new CsInterface().TransformText());
            Generator.WriteFile(Path.Combine(path, "ClientPrivate.cs"), new CsImpl().TransformText());
            Generator.WriteFile(Path.Combine(path, "ClientPrivateWindows.cs"), new CsImplWindows().TransformText());
            foreach (GameFile file in gameDef.Files)
            {
                CurrentFile = file;
                Generator.WriteFile(Path.Combine(path, string.Format("{0}.cs", Case.CamelCase.Convert(file.Name))), new CsHeader().TransformText());
            }
        }

        public static int GetSerializedMemberCount(string type)
        {
            if (Definition.GetBasicType(type) != BasicType.Class)
                return 1;
            if (Definition.Class[type].HasId)
                return Definition.Class[type].Id.Member.Count;
            return Definition.Class[type].Member.Sum(m => GetSerializedMemberCount(m.Type));
        }

        public static string GetSerializedMemberString(string parentName, string type, string name)
        {
            switch (Definition.GetBasicType(type))
            {
                case BasicType.Bool:
                    return string.Format("{0}{1} ? 1 : 0", parentName, name);
                case BasicType.Char:
                case BasicType.Enum:
                    return string.Format("(int){0}{1}", parentName, name);
                case BasicType.Class:
                    if (Definition.Class[type].HasId)
                    {
                        return string.Join(", ", Definition.Class[type].Id.Member.Select(m => string.Format("({0}{1} != null) ? ({2}) : -1", parentName, name, GetSerializedMemberString(string.Format("{0}{1}.", parentName, name), Definition.Class[type].MemberMap[m].Type, Case.CamelCase.Convert(m)))));
                    }
                    else
                    {
                        return string.Join(", ", Definition.Class[type].Member.Select(m => GetSerializedMemberString(string.Format("{0}{1}.", parentName, name), m.Type, Case.CamelCase.Convert(m.Name))));
                    }
                default:
                    return string.Format("{0}{1}", parentName, name);
            }
        }

        public static string GetBasicTypeName(BasicType type)
        {
            switch (type)
            {
                case BasicType.Bool:
                    return "bool";
                case BasicType.Char:
                    return "char";
                case BasicType.Void:
                    return "void";
                case BasicType.Class:
                    return "class";
                case BasicType.Enum:
                    return "enum";
                case BasicType.U8:
                    return "byte";
                case BasicType.U16:
                    return "ushort";
                case BasicType.U32:
                    return "uint";
                case BasicType.U64:
                    return "ulong";
                case BasicType.I8:
                    return "sbyte";
                case BasicType.I16:
                    return "short";
                case BasicType.I32:
                    return "int";
                case BasicType.I64:
                    return "long";
                default:
                    throw new NotImplementedException();
            }
        }
    }
}
