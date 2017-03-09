﻿// ------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version: 14.0.0.0
//  
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
// ------------------------------------------------------------------------------
namespace ugly.CodeGenerator.cxx
{
    using System.Linq;
    using System.Text;
    using System.Collections.Generic;
    using System;
    
    /// <summary>
    /// Class to produce the template output
    /// </summary>
    
    #line 1 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.TextTemplating", "14.0.0.0")]
    public partial class CxxImpl : CxxImplBase
    {
#line hidden
        /// <summary>
        /// Create the template output
        /// </summary>
        public virtual string TransformText()
        {
            this.Write("#include \"Client.h\"\r\n#include <string>\r\n#include <iostream>\r\n#include <cstdint>\r\n" +
                    "#include <cctype>\r\n#include <sstream>\r\n\r\nnamespace ");
            
            #line 13 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.Namespace)));
            
            #line default
            #line hidden
            this.Write("\r\n{\r\n    GameClient::~GameClient() {}\r\n\r\n    namespace\r\n    {\r\n        ");
            
            #line 19 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
 this.PushIndent("        "); 
            
            #line default
            #line hidden
            this.Write(@"template<class T> T ReadNext(const char*& buf)
{
    std::uint64_t data = 0;
    bool negative = false;
    if (*buf == '-')
    {
        negative = true;
        ++buf;
    }
    while (std::isdigit(*buf))
    {
        data *= 10;
        data += ((*buf) - '0');
        ++buf;
    }
    if (*buf)
        ++buf;
    if (negative)
        return static_cast<T>(-static_cast<std::int64_t>(data));
    return static_cast<T>(data);
}

template<class T> void Deserialize(T& data, const char*& buf, ");
            
            #line 23 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write("* gameSetup, ");
            
            #line 23 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write("* gameState");
            
            #line 23 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

    if (CxxHelper.Server)
    {
        
            
            #line default
            #line hidden
            this.Write(", Serializer::IdMap* idSetup, Serializer::IdMap* idState");
            
            #line 26 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
 
    }
    
            
            #line default
            #line hidden
            this.Write(")\r\n{\r\n    data = ReadNext<T>(buf);\r\n}");
            
            #line 31 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"


foreach (GameClass c in CxxHelper.Definition.Class.Values)
{
    if (CxxHelper.Server && (c.HasId || !c.IsInMethodParam))
        continue;
    
            
            #line default
            #line hidden
            this.Write("    \r\ntemplate<> void Deserialize(");
            
            #line 39 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(c.Name)));
            
            #line default
            #line hidden
            this.Write("& data, const char*& buf, ");
            
            #line 39 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write("* gameSetup, ");
            
            #line 39 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write("* gameState");
            
            #line 39 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

    if (CxxHelper.Server)
    {
        
            
            #line default
            #line hidden
            this.Write(", Serializer::IdMap* idSetup, Serializer::IdMap* idState");
            
            #line 42 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
 
    }
    
            
            #line default
            #line hidden
            this.Write(");");
            
            #line 44 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

}
foreach (GameClass c in CxxHelper.Definition.Class.Values)
{
    if (CxxHelper.Server && (c.HasId || !c.IsInMethodParam))
        continue;
    
            
            #line default
            #line hidden
            this.Write("\r\n\r\ntemplate<> void Deserialize(");
            
            #line 53 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(c.Name)));
            
            #line default
            #line hidden
            this.Write("& data, const char*& buf, ");
            
            #line 53 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write("* gameSetup, ");
            
            #line 53 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write("* gameState");
            
            #line 53 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

    if (CxxHelper.Server)
    {
        
            
            #line default
            #line hidden
            this.Write(", Serializer::IdMap* idSetup, Serializer::IdMap* idState");
            
            #line 56 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
 
    }
    
            
            #line default
            #line hidden
            this.Write(")\r\n{");
            
            #line 59 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

    foreach (ClassMember m in c.Member)
    {
        if (!CxxHelper.Server && ((c.HasId && c.Id.Index && c.Id.Member.Contains(m.Name)) || (m.Index == ClassMemberIndexType.MappedFromStrong)))
        {
            continue;
        }
        
            
            #line default
            #line hidden
            this.Write("\r\n    {\r\n        auto& member = data.");
            
            #line 69 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(m.Name)));
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 69 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"


        if (m.IsWeak && CxxHelper.Definition.Class[m.Type].Id.Index)
        {
            GameClass realType = CxxHelper.Definition.Class[m.Type];
            foreach (string deserializeStr in CxxHelper.GetDeserializeIndexedClass(realType, "member", "(*gameSetup)", "(*gameState)", true))
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n        ");
            
            #line 78 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(deserializeStr));
            
            #line default
            #line hidden
            
            #line 78 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

            }
        }
        else if (m.IsWeak && !c.Id.Index && CxxHelper.Server)
        {
            
            
            #line default
            #line hidden
            this.Write("        {\r\n            int classIdx = ReadNext<int>(buf);\r\n            member = n" +
                    "ullptr;\r\n            if (idState != nullptr)\r\n            {\r\n                aut" +
                    "o classIt = idState->");
            
            #line 89 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(m.Type)));
            
            #line default
            #line hidden
            this.Write(".find(classIdx);\r\n                if (classIt != idState->");
            
            #line 90 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(m.Type)));
            
            #line default
            #line hidden
            this.Write(".end())\r\n                {\r\n                    member = classIt->second;\r\n      " +
                    "          }\r\n            }\r\n            if (member == nullptr && idSetup != null" +
                    "ptr)\r\n            {\r\n                auto classIt = idSetup->");
            
            #line 97 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(m.Type)));
            
            #line default
            #line hidden
            this.Write(".find(classIdx);\r\n                if (classIt != idSetup->");
            
            #line 98 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(m.Type)));
            
            #line default
            #line hidden
            this.Write(".end())\r\n                {\r\n                    member = classIt->second;\r\n      " +
                    "          }\r\n            }\r\n        }");
            
            #line 103 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

        }
        else
        {
            for (int i = 0; i < m.Array; ++i)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n        int size");
            
            #line 111 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(" = ReadNext<int>(buf);");
            
            #line 111 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

            }
            if (m.Array != 0)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n        auto& array0 = member;\r\n        array0.resize(size0);");
            
            #line 118 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

            }
            for (int i = 1; i < m.Array; ++i)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n        for (int idx");
            
            #line 124 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i - 1));
            
            #line default
            #line hidden
            this.Write(" = 0; idx");
            
            #line 124 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i - 1));
            
            #line default
            #line hidden
            this.Write(" < size");
            
            #line 124 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i - 1));
            
            #line default
            #line hidden
            this.Write("; ++idx");
            
            #line 124 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i - 1));
            
            #line default
            #line hidden
            this.Write(")\r\n        {\r\n            auto& array");
            
            #line 126 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(" = array");
            
            #line 126 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i - 1));
            
            #line default
            #line hidden
            this.Write("[idx");
            
            #line 126 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i - 1));
            
            #line default
            #line hidden
            this.Write("];\r\n            array");
            
            #line 127 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(".resize(size");
            
            #line 127 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(");");
            
            #line 127 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                this.PushIndent("    ");
            }
            for (int i = 1; i < m.Array; ++i)
            {
                this.PopIndent();
                
            
            #line default
            #line hidden
            this.Write("\r\n        }");
            
            #line 135 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

            }
            for (int i = 0; i < m.Array; ++i)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n        for (int idx");
            
            #line 141 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(" = 0; idx");
            
            #line 141 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(" < size");
            
            #line 141 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write("; ++idx");
            
            #line 141 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(")\r\n        {\r\n            auto& array");
            
            #line 143 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i + 1));
            
            #line default
            #line hidden
            this.Write(" = array");
            
            #line 143 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write("[idx");
            
            #line 143 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write("];");
            
            #line 143 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                this.PushIndent("    ");
            }
            if (m.Array != 0)
            {
            
            
            #line default
            #line hidden
            this.Write("\r\n        Deserialize(array");
            
            #line 150 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(m.Array));
            
            #line default
            #line hidden
            this.Write(", buf, gameSetup, gameState");
            
            #line 150 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                if (CxxHelper.Server)
                {
                    
            
            #line default
            #line hidden
            this.Write(", idSetup, idState");
            
            #line 153 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                }
                
            
            #line default
            #line hidden
            this.Write(");");
            
            #line 155 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                if (m.Index == ClassMemberIndexType.Strong)
                {
                    GameClass mType = CxxHelper.Definition.Class[m.Type];
                    if (mType.HasId && mType.Id.Index)
                    {
                        for (int i = 0; i < mType.Id.Member.Count; ++i)
                        {
                            
            
            #line default
            #line hidden
            this.Write("\r\n        array");
            
            #line 165 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(m.Array));
            
            #line default
            #line hidden
            this.Write(".");
            
            #line 165 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(mType.Id.Member[i])));
            
            #line default
            #line hidden
            this.Write(" = idx");
            
            #line 165 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 165 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                        }
                    }
                    foreach (IndexMapping mapping in mType.IndexMapping)
                    {
                        List<IndexMapping> indexMapping = mapping.Member.SelectMany(mappingMember => mappingMember.Index).ToList();
                        if (indexMapping.Any())
                        {
                            
            
            #line default
            #line hidden
            this.Write("\r\n        if (");
            
            #line 175 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(string.Join(" && ", indexMapping.Select(idxMapping => string.Format("{0} >= 0", idxMapping.FormatMapping(Case.LowerCamelCase, string.Format("array{0}", m.Array), "(*gameSetup)", "(*gameState)"))))));
            
            #line default
            #line hidden
            this.Write(")\r\n        {");
            
            #line 176 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                            this.PushIndent("    ");
                        }
                        
            
            #line default
            #line hidden
            this.Write("\r\n        ");
            
            #line 181 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(mapping.FormatMapping(Case.LowerCamelCase, string.Format("array{0}", m.Array), "(*gameSetup)", "(*gameState)")));
            
            #line default
            #line hidden
            
            #line 181 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                        ClassMember mapped = mapping.GetMember(CxxHelper.Definition);
                        if (mapped.Array == 0)
                        {
                            
            
            #line default
            #line hidden
            this.Write(" = &array");
            
            #line 185 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(m.Array));
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 185 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                        }
                        else if (mapped.Array == 1)
                        {
                            
            
            #line default
            #line hidden
            this.Write(".push_back(&array");
            
            #line 189 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(m.Array));
            
            #line default
            #line hidden
            this.Write(");");
            
            #line 189 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                        }
                        else
                        {
                            throw new Exception("Unsupported arity > 1 for mapping");
                        }
                        if (indexMapping.Any())
                        {
                            this.PopIndent();
                            
            
            #line default
            #line hidden
            this.Write("\r\n        }");
            
            #line 200 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                        }
                    }
                }
            }
            else
            {
            
            
            #line default
            #line hidden
            this.Write("\r\n        Deserialize(member, buf, gameSetup, gameState");
            
            #line 209 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                if (CxxHelper.Server)
                {
                    
            
            #line default
            #line hidden
            this.Write(", idSetup, idState");
            
            #line 212 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

                }
                
            
            #line default
            #line hidden
            this.Write(");");
            
            #line 214 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

            }
            for (int i = 0; i < m.Array; ++i)
            {
                this.PopIndent();
            
            
            #line default
            #line hidden
            this.Write("\r\n        }");
            
            #line 221 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

            }
        }
        
            
            #line default
            #line hidden
            this.Write("\r\n    }");
            
            #line 226 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

    }
    
            
            #line default
            #line hidden
            this.Write("\r\n}");
            
            #line 230 "D:\ugly\CodeGenerator\cxx\CxxDeserializerInc.tt"

        
}

            
            #line default
            #line hidden
            this.Write("        ");
            
            #line 21 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
 this.PopIndent(); 
            
            #line default
            #line hidden
            this.Write(@"
    }
    
    void GameServer::Play(GameClient& client)
    {
        std::string line;
        std::getline(std::cin, line);
        const char* buf = line.c_str();
        int playerId = ReadNext<int>(buf);
        std::getline(std::cin, line);
        buf = line.c_str();
        ");
            
            #line 33 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write(@" data;
        Deserialize(data, buf, &data, nullptr);
        client.InitGame(data, data.player[playerId]);
        for (;;)
        {
            printf(""EOT\n"");
            std::getline(std::cin, line);
            if (line.compare(0, 3, ""EOT"") == 0)
                break;
            buf = line.c_str();
            ");
            
            #line 43 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write(@" turn;
            Deserialize(turn, buf, &data, &turn);
            client.PlayTurn(turn, turn.player[playerId]);
        }
        client.Cleanup();
        printf(""EOT\n"");
    }

    std::vector<std::pair<int, int>> GameServer::PlayLocalServer(GameClient& client, const std::string& serverPath, const std::vector<std::string>& otherPlayers, const std::string& game, const std::string& serverArgs)
    {
        std::stringstream commandLine;
        commandLine << '""' << serverPath << ""\"" -game \"""" << game << ""\"" -player parent;"";
        for (const std::string& player : otherPlayers)
            commandLine << "" -player \"""" << player << '""';
        if (!serverArgs.empty())
            commandLine << ' ' << serverArgs;
        return PlayLocalServerCommandLine(client, commandLine.str());
    }

    std::vector<std::pair<int, int>> GameServer::PlayLocalServerCommandLine(GameClient& client, const std::string& commandLine)
    {
        if (!StartLocalServer(commandLine))
            return {};
        Play(client);
        std::string line;
        std::getline(std::cin, line);
        const char* buf = line.c_str();
        std::vector<std::pair<int, int>> results;
        for (;;)
        {
            int rank = ReadNext<int>(buf);
            if (rank == 0)
                return results;
            results.push_back({rank, ReadNext<int>(buf)});
        }
    }
}");
            return this.GenerationEnvironment.ToString();
        }
    }
    
    #line default
    #line hidden
    #region Base class
    /// <summary>
    /// Base class for this transformation
    /// </summary>
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.TextTemplating", "14.0.0.0")]
    public class CxxImplBase
    {
        #region Fields
        private global::System.Text.StringBuilder generationEnvironmentField;
        private global::System.CodeDom.Compiler.CompilerErrorCollection errorsField;
        private global::System.Collections.Generic.List<int> indentLengthsField;
        private string currentIndentField = "";
        private bool endsWithNewline;
        private global::System.Collections.Generic.IDictionary<string, object> sessionField;
        #endregion
        #region Properties
        /// <summary>
        /// The string builder that generation-time code is using to assemble generated output
        /// </summary>
        protected System.Text.StringBuilder GenerationEnvironment
        {
            get
            {
                if ((this.generationEnvironmentField == null))
                {
                    this.generationEnvironmentField = new global::System.Text.StringBuilder();
                }
                return this.generationEnvironmentField;
            }
            set
            {
                this.generationEnvironmentField = value;
            }
        }
        /// <summary>
        /// The error collection for the generation process
        /// </summary>
        public System.CodeDom.Compiler.CompilerErrorCollection Errors
        {
            get
            {
                if ((this.errorsField == null))
                {
                    this.errorsField = new global::System.CodeDom.Compiler.CompilerErrorCollection();
                }
                return this.errorsField;
            }
        }
        /// <summary>
        /// A list of the lengths of each indent that was added with PushIndent
        /// </summary>
        private System.Collections.Generic.List<int> indentLengths
        {
            get
            {
                if ((this.indentLengthsField == null))
                {
                    this.indentLengthsField = new global::System.Collections.Generic.List<int>();
                }
                return this.indentLengthsField;
            }
        }
        /// <summary>
        /// Gets the current indent we use when adding lines to the output
        /// </summary>
        public string CurrentIndent
        {
            get
            {
                return this.currentIndentField;
            }
        }
        /// <summary>
        /// Current transformation session
        /// </summary>
        public virtual global::System.Collections.Generic.IDictionary<string, object> Session
        {
            get
            {
                return this.sessionField;
            }
            set
            {
                this.sessionField = value;
            }
        }
        #endregion
        #region Transform-time helpers
        /// <summary>
        /// Write text directly into the generated output
        /// </summary>
        public void Write(string textToAppend)
        {
            if (string.IsNullOrEmpty(textToAppend))
            {
                return;
            }
            // If we're starting off, or if the previous text ended with a newline,
            // we have to append the current indent first.
            if (((this.GenerationEnvironment.Length == 0) 
                        || this.endsWithNewline))
            {
                this.GenerationEnvironment.Append(this.currentIndentField);
                this.endsWithNewline = false;
            }
            // Check if the current text ends with a newline
            if (textToAppend.EndsWith(global::System.Environment.NewLine, global::System.StringComparison.CurrentCulture))
            {
                this.endsWithNewline = true;
            }
            // This is an optimization. If the current indent is "", then we don't have to do any
            // of the more complex stuff further down.
            if ((this.currentIndentField.Length == 0))
            {
                this.GenerationEnvironment.Append(textToAppend);
                return;
            }
            // Everywhere there is a newline in the text, add an indent after it
            textToAppend = textToAppend.Replace(global::System.Environment.NewLine, (global::System.Environment.NewLine + this.currentIndentField));
            // If the text ends with a newline, then we should strip off the indent added at the very end
            // because the appropriate indent will be added when the next time Write() is called
            if (this.endsWithNewline)
            {
                this.GenerationEnvironment.Append(textToAppend, 0, (textToAppend.Length - this.currentIndentField.Length));
            }
            else
            {
                this.GenerationEnvironment.Append(textToAppend);
            }
        }
        /// <summary>
        /// Write text directly into the generated output
        /// </summary>
        public void WriteLine(string textToAppend)
        {
            this.Write(textToAppend);
            this.GenerationEnvironment.AppendLine();
            this.endsWithNewline = true;
        }
        /// <summary>
        /// Write formatted text directly into the generated output
        /// </summary>
        public void Write(string format, params object[] args)
        {
            this.Write(string.Format(global::System.Globalization.CultureInfo.CurrentCulture, format, args));
        }
        /// <summary>
        /// Write formatted text directly into the generated output
        /// </summary>
        public void WriteLine(string format, params object[] args)
        {
            this.WriteLine(string.Format(global::System.Globalization.CultureInfo.CurrentCulture, format, args));
        }
        /// <summary>
        /// Raise an error
        /// </summary>
        public void Error(string message)
        {
            System.CodeDom.Compiler.CompilerError error = new global::System.CodeDom.Compiler.CompilerError();
            error.ErrorText = message;
            this.Errors.Add(error);
        }
        /// <summary>
        /// Raise a warning
        /// </summary>
        public void Warning(string message)
        {
            System.CodeDom.Compiler.CompilerError error = new global::System.CodeDom.Compiler.CompilerError();
            error.ErrorText = message;
            error.IsWarning = true;
            this.Errors.Add(error);
        }
        /// <summary>
        /// Increase the indent
        /// </summary>
        public void PushIndent(string indent)
        {
            if ((indent == null))
            {
                throw new global::System.ArgumentNullException("indent");
            }
            this.currentIndentField = (this.currentIndentField + indent);
            this.indentLengths.Add(indent.Length);
        }
        /// <summary>
        /// Remove the last indent that was added with PushIndent
        /// </summary>
        public string PopIndent()
        {
            string returnValue = "";
            if ((this.indentLengths.Count > 0))
            {
                int indentLength = this.indentLengths[(this.indentLengths.Count - 1)];
                this.indentLengths.RemoveAt((this.indentLengths.Count - 1));
                if ((indentLength > 0))
                {
                    returnValue = this.currentIndentField.Substring((this.currentIndentField.Length - indentLength));
                    this.currentIndentField = this.currentIndentField.Remove((this.currentIndentField.Length - indentLength));
                }
            }
            return returnValue;
        }
        /// <summary>
        /// Remove any indentation
        /// </summary>
        public void ClearIndent()
        {
            this.indentLengths.Clear();
            this.currentIndentField = "";
        }
        #endregion
        #region ToString Helpers
        /// <summary>
        /// Utility class to produce culture-oriented representation of an object as a string.
        /// </summary>
        public class ToStringInstanceHelper
        {
            private System.IFormatProvider formatProviderField  = global::System.Globalization.CultureInfo.InvariantCulture;
            /// <summary>
            /// Gets or sets format provider to be used by ToStringWithCulture method.
            /// </summary>
            public System.IFormatProvider FormatProvider
            {
                get
                {
                    return this.formatProviderField ;
                }
                set
                {
                    if ((value != null))
                    {
                        this.formatProviderField  = value;
                    }
                }
            }
            /// <summary>
            /// This is called from the compile/run appdomain to convert objects within an expression block to a string
            /// </summary>
            public string ToStringWithCulture(object objectToConvert)
            {
                if ((objectToConvert == null))
                {
                    throw new global::System.ArgumentNullException("objectToConvert");
                }
                System.Type t = objectToConvert.GetType();
                System.Reflection.MethodInfo method = t.GetMethod("ToString", new System.Type[] {
                            typeof(System.IFormatProvider)});
                if ((method == null))
                {
                    return objectToConvert.ToString();
                }
                else
                {
                    return ((string)(method.Invoke(objectToConvert, new object[] {
                                this.formatProviderField })));
                }
            }
        }
        private ToStringInstanceHelper toStringHelperField = new ToStringInstanceHelper();
        /// <summary>
        /// Helper to produce culture-oriented representation of an object as a string
        /// </summary>
        public ToStringInstanceHelper ToStringHelper
        {
            get
            {
                return this.toStringHelperField;
            }
        }
        #endregion
    }
    #endregion
}
