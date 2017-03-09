using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ugly.CodeGenerator.cxx
{

    public static class CxxHelper
    {
        public static GameDefinition Definition { get; private set; }
        public static GameFile CurrentFile { get; private set; }
        public static bool Server { get; private set; }

        public static void GenerateFiles(string path, GameDefinition gameDef)
        {
            Server = false;
            Definition = gameDef;
            Directory.CreateDirectory(path);
            Generator.WriteFile(Path.Combine(path, "Client.h"), new CxxInterface().TransformText());
            Generator.WriteFile(Path.Combine(path, "Client.cpp"), new CxxImpl().TransformText());
            Generator.WriteFile(Path.Combine(path, "ClientWindows.cpp"), new CxxImplWindows().TransformText());
            foreach (GameFile file in gameDef.Files)
            {
                CurrentFile = file;
                Generator.WriteFile(Path.Combine(path, string.Format("{0}.h", Case.CamelCase.Convert(file.Name))), new CxxHeader().TransformText());
                Generator.WriteFile(Path.Combine(path, string.Format("{0}.cpp", Case.CamelCase.Convert(file.Name))), new CxxCode().TransformText());
            }
        }

        public static void GenerateServerFiles(string path, GameDefinition gameDef)
        {
            Server = true;
            Definition = gameDef;
            Directory.CreateDirectory(path);
            Generator.WriteFile(Path.Combine(path, "Serializer.h"), new CxxSerializerHeader().TransformText());
            Generator.WriteFile(Path.Combine(path, "Serializer.cpp"), new CxxSerializationCode().TransformText());
            Generator.WriteFile(Path.Combine(path, "Game.h"), new CxxServerHeader().TransformText());
            Generator.WriteFile(Path.Combine(path, "Game.cpp"), new CxxServerCode().TransformText());
            foreach (GameFile file in gameDef.Files)
            {
                CurrentFile = file;
                Generator.WriteFile(Path.Combine(path, string.Format("{0}.h", Case.CamelCase.Convert(file.Name))), new CxxHeader().TransformText());
                Generator.WriteFile(Path.Combine(path, string.Format("{0}.cpp", Case.CamelCase.Convert(file.Name))), new CxxCode().TransformText());
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
                    return "struct";
                case BasicType.Enum:
                    return "enum class";
                case BasicType.U8:
                    return "std::uint8_t";
                case BasicType.U16:
                    return "std::uint16_t";
                case BasicType.U32:
                    return "std::uint32_t";
                case BasicType.U64:
                    return "std::uint64_t";
                case BasicType.I8:
                    return "std::int8_t";
                case BasicType.I16:
                    return "std::int16_t";
                case BasicType.I32:
                    return "std::int32_t";
                case BasicType.I64:
                    return "std::int64_t";
                default:
                    throw new NotImplementedException();
            }
        }

        public static string GetSerializedFormatString(string type)
        {
            switch (Definition.GetBasicType(type))
            {
                case BasicType.Bool:
                case BasicType.Char:
                case BasicType.Enum:
                case BasicType.I8:
                case BasicType.I16:
                case BasicType.I32:
                    return "%d";
                case BasicType.U8:
                case BasicType.U16:
                case BasicType.U32:
                    return "%u";
                case BasicType.U64:
                    return "%llu";
                case BasicType.I64:
                    return "%lld";
                case BasicType.Class:
                    if (Definition.Class[type].HasId)
                    {
                        return string.Join(" ", Definition.Class[type].Id.Member.Select(m => GetSerializedFormatString(Definition.Class[type].MemberMap[m].Type)));
                    }
                    else
                    {
                        return string.Join(" ", Definition.Class[type].Member.Select(m => GetSerializedFormatString(m.Type)));
                    }
                default:
                    throw new Exception("Unknown type");
            }
        }

        public static string GetSerializedMemberString(string parentName, string type, string name)
        {
            switch (Definition.GetBasicType(type))
            {
                case BasicType.Enum:
                    return string.Format("(int){0}{1}", parentName, name);
                case BasicType.Class:
                    if (Definition.Class[type].HasId)
                    {
                        return string.Join(", ", Definition.Class[type].Id.Member.Select(m => string.Format("({0}{1} != nullptr) ? ({2}) : -1", parentName, name, GetSerializedMemberString(string.Format("{0}{1}->", parentName, name), Definition.Class[type].MemberMap[m].Type, Case.LowerCamelCase.Convert(m)))));
                    }
                    else
                    {
                        return string.Join(", ", Definition.Class[type].Member.Select(m => GetSerializedMemberString(string.Format("{0}{1}.", parentName, name), m.Type, Case.CamelCase.Convert(m.Name))));
                    }
                default:
                    return string.Format("{0}{1}", parentName, name);
            }
        }
    }
}
