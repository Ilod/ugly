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
            File.WriteAllText(Path.Combine(path, "Client.cs"), new CsInterface().TransformText());
            File.WriteAllText(Path.Combine(path, "ClientPrivate.cs"), new CsImpl().TransformText());
            foreach (GameFile file in gameDef.Files)
            {
                CurrentFile = file;
                File.WriteAllText(Path.Combine(path, string.Format("{0}.cs", Case.CamelCase.Convert(file.Name))), new CsHeader().TransformText());
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
