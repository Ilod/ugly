using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ugly
{
    namespace CodeGenerator
    {
        public enum Case
        {
            CCase,
            CamelCase,
            LowerCamelCase,
            AllCaps,
        }

        public static class Generator
        {
            public static string Namespace = "FreeMarket";

            public static bool WriteFile(string path, string text)
            {
                if (File.Exists(path) && File.ReadAllText(path) == text)
                    return false;
                File.WriteAllText(path, text);
                return true;
            }

            public static bool IsBasic(this BasicType type)
            {
                switch (type)
                {
                    case BasicType.Class:
                    case BasicType.Enum:
                        return false;
                    default:
                        return true;
                }
            }

            public static string Convert(this Case config, string text)
            {
                switch (config)
                {
                    case Case.CCase:
                        return text;
                    case Case.AllCaps:
                        return text.ToUpperInvariant();
                    case Case.CamelCase:
                        return string.Join("", text.Split(new char[] { '_' }).Select(str => char.ToUpperInvariant(str[0]) + str.Substring(1)));
                    case Case.LowerCamelCase:
                        {
                            string[] splitted = text.Split(new char[] { '_' });
                            return splitted[0] + string.Join("", splitted.Skip(1).Select(str => char.ToUpperInvariant(str[0]) + str.Substring(1)));
                        }
                }
                return text;

            }

            static int Main(string[] args)
            {
                SharpYaml.Serialization.Serializer serializer = new SharpYaml.Serialization.Serializer();
                if (args.Length != 1)
                {
                    Console.Error.WriteLine("You must provide an input YAML file!");
                    Console.In.Read();
                    return 1;
                }
                try
                {
                    GameDefinition def = serializer.Deserialize(File.ReadAllText(args[0]), typeof(GameDefinition)) as GameDefinition;
                    def.ParseTypes();
                    string baseDir = Directory.GetCurrentDirectory();
                    if (args.Length > 1)
                    {
                        baseDir = args[1];
                    }
                    cxx.CxxHelper.GenerateFiles(Path.Combine(baseDir, "cxx"), def);
                    cxx.CxxHelper.GenerateServerFiles(Path.Combine(baseDir, "server"), def);
                    cs.CsHelper.GenerateFiles(Path.Combine(baseDir, "cs"), def);
                    return 0;
                }
                catch (Exception e)
                {
                    Console.Error.WriteLine(e);
                    Console.In.Read();
                    return 1;
                }
            }
        }
    }
}
