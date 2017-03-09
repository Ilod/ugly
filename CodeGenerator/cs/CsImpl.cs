﻿// ------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version: 14.0.0.0
//  
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
// ------------------------------------------------------------------------------
namespace ugly.CodeGenerator.cs
{
    using System.Linq;
    using System.Text;
    using System.Collections.Generic;
    using System;
    
    /// <summary>
    /// Class to produce the template output
    /// </summary>
    
    #line 1 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.TextTemplating", "14.0.0.0")]
    public partial class CsImpl : CsImplBase
    {
#line hidden
        /// <summary>
        /// Create the template output
        /// </summary>
        public virtual string TransformText()
        {
            this.Write("using System;\r\nusing System.IO;\r\n\r\nnamespace ");
            
            #line 9 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.Namespace)));
            
            #line default
            #line hidden
            this.Write("\r\n{\r\n    public static partial class GameServer\r\n    {\r\n        private static ");
            
            #line 13 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write(" ReadTurn(");
            
            #line 13 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write(" gameSetup)\r\n        {\r\n            Console.WriteLine(\"EOT\");\r\n            string" +
                    " line = Console.ReadLine();\r\n            if (line.StartsWith(\"EOT\"))\r\n          " +
                    "      return null;\r\n            Parser parser = new Parser(line);\r\n            ");
            
            #line 20 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write(" turn = new ");
            
            #line 20 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write("();\r\n            parser.Deserialize(turn, gameSetup, turn);\r\n            return t" +
                    "urn;\r\n        }\r\n        \r\n        private static Tuple<");
            
            #line 25 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write(", ");
            
            #line 25 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.PlayerSetup)));
            
            #line default
            #line hidden
            this.Write(@"> ReadSetup()
        {
            string line = Console.ReadLine();
            Parser parser = new Parser(line);
            int playerId = parser.ReadNextInt();
            line = Console.ReadLine();
            parser = new Parser(line);
            ");
            
            #line 32 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write(" data = new ");
            
            #line 32 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write("();\r\n            parser.Deserialize(data, data, null);\r\n            return Tuple." +
                    "Create(data, data.Player[playerId]);\r\n        }\r\n\r\n        private class Parser\r" +
                    "\n        {\r\n            private string Line;\r\n            private int Index = 0;" +
                    "\r\n\r\n            public Parser(string line)\r\n            {\r\n                Line " +
                    "= line;\r\n            }\r\n\r\n            public long ReadNextLong()\r\n            {\r" +
                    "\n                long data = 0;\r\n                bool negative = false;\r\n       " +
                    "         if (Index < Line.Length && Line[Index] == \'-\')\r\n                {\r\n    " +
                    "                negative = true;\r\n                    ++Index;\r\n                " +
                    "}\r\n\r\n                while (Index < Line.Length && Line[Index] >= \'0\' && Line[In" +
                    "dex] <= \'9\')\r\n                {\r\n                    data *= 10;\r\n              " +
                    "      data += (long)(Line[Index] - \'0\');\r\n                    ++Index;\r\n        " +
                    "        }\r\n                ++Index;\r\n                return negative ? -data : d" +
                    "ata;\r\n            }\r\n            \r\n            public ulong ReadNextUlong()\r\n   " +
                    "         {\r\n                ulong data = 0;\r\n\r\n                while (Index < Li" +
                    "ne.Length && Line[Index] >= \'0\' && Line[Index] <= \'9\')\r\n                {\r\n     " +
                    "               data *= 10;\r\n                    data += (ulong)(Line[Index] - \'0" +
                    "\');\r\n                    ++Index;\r\n                }\r\n                ++Index;\r\n" +
                    "                return data;\r\n            }\r\n            \r\n            public in" +
                    "t ReadNextInt()\r\n            {\r\n                return (int)ReadNextLong();\r\n   " +
                    "         }\r\n            \r\n            public short ReadNextShort()\r\n            " +
                    "{\r\n                return (short)ReadNextLong();\r\n            }\r\n            \r\n " +
                    "           public sbyte ReadNextSbyte()\r\n            {\r\n                return (" +
                    "sbyte)ReadNextLong();\r\n            }\r\n            \r\n            public uint Read" +
                    "NextUint()\r\n            {\r\n                return (uint)ReadNextUlong();\r\n      " +
                    "      }\r\n            \r\n            public ushort ReadNextUshort()\r\n            {" +
                    "\r\n                return (ushort)ReadNextUlong();\r\n            }\r\n            \r\n" +
                    "            public byte ReadNextByte()\r\n            {\r\n                return (b" +
                    "yte)ReadNextUlong();\r\n            }\r\n            \r\n            public char ReadN" +
                    "extChar()\r\n            {\r\n                return (char)ReadNextUlong();\r\n       " +
                    "     }\r\n            \r\n            public bool ReadNextBool()\r\n            {\r\n   " +
                    "             return ReadNextLong() != 0;\r\n            }");
            
            #line 119 "D:\ugly\CodeGenerator\cs\CsImpl.tt"


        foreach (GameClass c in CsHelper.Definition.Class.Values)
        {
            
            
            #line default
            #line hidden
            this.Write("\r\n\r\n            public void Deserialize(");
            
            #line 126 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(c.Name)));
            
            #line default
            #line hidden
            this.Write(" data, ");
            
            #line 126 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write(" gameSetup, ");
            
            #line 126 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write(" gameState)\r\n            {");
            
            #line 127 "D:\ugly\CodeGenerator\cs\CsImpl.tt"


            foreach (ClassMember m in c.Member)
            {
                if ((c.HasId && c.Id.Index && c.Id.Member.Contains(m.Name)) || (m.Index == ClassMemberIndexType.MappedFromStrong))
                {
                    continue;
                }
                
            
            #line default
            #line hidden
            this.Write("\r\n                {");
            
            #line 137 "D:\ugly\CodeGenerator\cs\CsImpl.tt"


                BasicType type = CsHelper.Definition.GetBasicType(m.Type);
                if (m.Array == 0)
                {
                    if (type.IsBasic())
                    {
                        
            
            #line default
            #line hidden
            this.Write("\r\n                    data.");
            
            #line 146 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Name)));
            
            #line default
            #line hidden
            this.Write(" = ReadNext");
            
            #line 146 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.GetBasicTypeName(type))));
            
            #line default
            #line hidden
            this.Write("();");
            
            #line 146 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    }
                    else if (type == BasicType.Class)
                    {
                        if (m.Index == ClassMemberIndexType.RefId)
                        {
                            GameClass realType = CsHelper.Definition.Class[m.Type];
                            for (int i = 0; i <= realType.Id.Member.Count; ++i)
                            {
                                
            
            #line default
            #line hidden
            this.Write("\r\n                    int classIdx");
            
            #line 157 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(" = ReadNext<int>();");
            
            #line 157 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                            }
                            
            
            #line default
            #line hidden
            this.Write("                            \r\n                    if (classIdx0 != -1)\r\n         " +
                    "           {\r\n                        data.");
            
            #line 163 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Name)));
            
            #line default
            #line hidden
            this.Write(" = ");
            
            #line 163 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(realType.Id.Source.FormatMapping(Case.CamelCase, null, "gameSetup", "gameState", ", ")));
            
            #line default
            #line hidden
            this.Write("[classIdx0");
            
            #line 163 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                            for (int i = 1; i <= c.Id.Member.Count; ++i)
                            {
                                
            
            #line default
            #line hidden
            this.Write(", classIdx");
            
            #line 166 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            
            #line 166 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                            }
                            
            
            #line default
            #line hidden
            this.Write("];\r\n                    }");
            
            #line 169 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                        }
                        else if (!m.IsWeak)
                        {
                            
            
            #line default
            #line hidden
            this.Write("\r\n                    Deserialize(data.");
            
            #line 175 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Name)));
            
            #line default
            #line hidden
            this.Write(", gameSetup, gameState);");
            
            #line 175 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                        }
                    }
                    else // Enum
                    {
                        
            
            #line default
            #line hidden
            this.Write("\r\n                    data.");
            
            #line 182 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Name)));
            
            #line default
            #line hidden
            this.Write(" = (");
            
            #line 182 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Type)));
            
            #line default
            #line hidden
            this.Write(")ReadNextInt();");
            
            #line 182 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    }
                }
                else if (!m.IsWeak)
                {
                    for (int i = 0; i < m.Array; ++i)
                    {
                            
            
            #line default
            #line hidden
            this.Write("\r\n                    int size");
            
            #line 191 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(" = ReadNextInt();");
            
            #line 191 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    }
            
            #line default
            #line hidden
            this.Write("\r\n                    data.");
            
            #line 194 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Name)));
            
            #line default
            #line hidden
            this.Write(" = new ");
            
            #line 194 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    if (type.IsBasic())
                    {
                        
            
            #line default
            #line hidden
            
            #line 197 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(CsHelper.GetBasicTypeName(type)));
            
            #line default
            #line hidden
            
            #line 197 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    }
                    else
                    {
                        
            
            #line default
            #line hidden
            
            #line 201 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Type)));
            
            #line default
            #line hidden
            
            #line 201 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    }
                    
            
            #line default
            #line hidden
            this.Write("[");
            
            #line 203 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    for (int i = 0; i < m.Array; ++i)
                    {
                        if (i != 0)
                        {
                            
            
            #line default
            #line hidden
            this.Write(", ");
            
            #line 208 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                        }
                        
            
            #line default
            #line hidden
            this.Write("size");
            
            #line 210 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            
            #line 210 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    }
                    
            
            #line default
            #line hidden
            this.Write("];");
            
            #line 212 "D:\ugly\CodeGenerator\cs\CsImpl.tt"


                    for (int i = 0; i < m.Array; ++i)
                    {
                        
            
            #line default
            #line hidden
            this.Write("\r\n                    for (int idx");
            
            #line 218 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(" = 0; idx");
            
            #line 218 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(" < size");
            
            #line 218 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write("; ++idx");
            
            #line 218 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(")\r\n                    {");
            
            #line 219 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                        this.PushIndent("    ");
                    }
                    if (type == BasicType.Class)
                    {
            
            #line default
            #line hidden
            this.Write("\r\n                    ");
            
            #line 225 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Type)));
            
            #line default
            #line hidden
            this.Write(" element = new ");
            
            #line 225 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Type)));
            
            #line default
            #line hidden
            this.Write("();\r\n                    Deserialize(element, gameSetup, gameState);");
            
            #line 226 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                        GameClass mType = CsHelper.Definition.Class[m.Type];
                        if (m.Index == ClassMemberIndexType.Strong && mType.HasId && mType.Id.Index)
                        {
                            for (int i = 0; i < mType.Id.Member.Count; ++i)
                            {
                                
            
            #line default
            #line hidden
            this.Write("\r\n                    element.");
            
            #line 234 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(mType.Id.Member[i])));
            
            #line default
            #line hidden
            this.Write(" = idx");
            
            #line 234 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 234 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                            }
                            foreach (IndexMapping mapping in mType.IndexMapping)
                            {
                                
            
            #line default
            #line hidden
            this.Write("\r\n                    ");
            
            #line 240 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(mapping.FormatMapping(Case.CamelCase, "element", "gameSetup", "gameState", ", ")));
            
            #line default
            #line hidden
            
            #line 240 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                                if (m.Array == 0)
                                {
                                    
            
            #line default
            #line hidden
            this.Write(" = element;");
            
            #line 243 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                                }
                                else if (m.Array == 1)
                                {
                                    
            
            #line default
            #line hidden
            this.Write(".Add(element);");
            
            #line 247 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                                }
                                else
                                {
                                    throw new Exception("Unsupported arity > 1 for mapping");
                                }
                            }
                        }
                    }
                        
            
            #line default
            #line hidden
            this.Write("\r\n                    data.");
            
            #line 258 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Name)));
            
            #line default
            #line hidden
            this.Write("[idx0");
            
            #line 258 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    for (int i = 1; i < m.Array; ++i)
                    {
                        
            
            #line default
            #line hidden
            this.Write(", idx");
            
            #line 261 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            
            #line 261 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    }
                    
            
            #line default
            #line hidden
            this.Write("] = ");
            
            #line 263 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    if (type == BasicType.Class)
                    {
                        
            
            #line default
            #line hidden
            this.Write("element");
            
            #line 266 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    }
                    else
                    {
                        
            
            #line default
            #line hidden
            this.Write("ReadNext");
            
            #line 270 "D:\ugly\CodeGenerator\cs\CsImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.GetBasicTypeName(type))));
            
            #line default
            #line hidden
            this.Write("()");
            
            #line 270 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    }
                    
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 272 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                
                    for (int i = 0; i < m.Array; ++i)
                    {
                        this.PopIndent();
                        
            
            #line default
            #line hidden
            this.Write("\r\n                    }");
            
            #line 279 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

                    }
                }
                
            
            #line default
            #line hidden
            this.Write("\r\n                }");
            
            #line 284 "D:\ugly\CodeGenerator\cs\CsImpl.tt"


            }         
            
            
            #line default
            #line hidden
            this.Write("           \r\n            }");
            
            #line 289 "D:\ugly\CodeGenerator\cs\CsImpl.tt"

        }
        
            
            #line default
            #line hidden
            this.Write("\r\n        }\r\n    }\r\n}");
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
    public class CsImplBase
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
