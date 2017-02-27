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
                    "#include <cctype>\r\n\r\nnamespace ");
            
            #line 12 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.Namespace)));
            
            #line default
            #line hidden
            this.Write(@"
{
    namespace
    {
        template<class T> T ReadNextInt(const char*& buf)
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
            }
            if (*buf)
                ++buf;
            if (negative)
                return static_cast<T>(-static_cast<int64_t>(data));
            return static_cast<T>(data);
        }

        template<class T> void Deserialize(T& data, const char*& buf)
        {
            data = ReadNextInt<T>(buf);
        }");
            
            #line 40 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

    foreach (GameClass c in CxxHelper.Definition.Class.Values)
    {
        
            
            #line default
            #line hidden
            this.Write("\r\n        template<> void Deserialize(");
            
            #line 45 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(c.Name)));
            
            #line default
            #line hidden
            this.Write("& data, const char*& buf);");
            
            #line 45 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

    }
    foreach (GameClass c in CxxHelper.Definition.Class.Values)
    {
        
            
            #line default
            #line hidden
            this.Write("\r\n\r\n        template<> void Deserialize(");
            
            #line 52 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(c.Name)));
            
            #line default
            #line hidden
            this.Write("& data, const char*& buf)\r\n        {");
            
            #line 53 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

        foreach (ClassMember m in c.Member)
        {
            
            
            #line default
            #line hidden
            this.Write("\r\n            {\r\n                auto& member = data.");
            
            #line 59 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(m.Name)));
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 59 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

            for (int i = 0; i < m.Array; ++i)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n                int size");
            
            #line 64 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(" = ReadNextInt<int>(buf);");
            
            #line 64 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

            }
            if (m.Array != 0)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n                auto& array0 = member;\r\n                array0.resize(size0);");
            
            #line 71 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

            }
            for (int i = 1; i < m.Array; ++i)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n                for (int idx");
            
            #line 77 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i - 1));
            
            #line default
            #line hidden
            this.Write(" = 0; i < size");
            
            #line 77 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i - 1));
            
            #line default
            #line hidden
            this.Write("; ++i)\r\n                {\r\n                    auto& array");
            
            #line 79 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(" = array");
            
            #line 79 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i - 1));
            
            #line default
            #line hidden
            this.Write("[idx");
            
            #line 79 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i - 1));
            
            #line default
            #line hidden
            this.Write("];\r\n                    array");
            
            #line 80 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(".resize(size");
            
            #line 80 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(");");
            
            #line 80 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

            }
            for (int i = 1; i < m.Array; ++i)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n                }");
            
            #line 86 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

            }
            for (int i = 0; i < m.Array; ++i)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n                for (int idx");
            
            #line 92 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write(" = 0; i < size");
            
            #line 92 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write("; ++i)\r\n                {\r\n                    auto& array");
            
            #line 94 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i + 1));
            
            #line default
            #line hidden
            this.Write(" = array");
            
            #line 94 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write("[idx");
            
            #line 94 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            this.Write("];");
            
            #line 94 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

            }
            if (m.Array != 0)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n                    Deserialize(array");
            
            #line 100 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(m.Array));
            
            #line default
            #line hidden
            this.Write(", buf);");
            
            #line 100 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

            }
            else
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n                Deserialize(member, buf);");
            
            #line 106 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

            }
            for (int i = 0; i < m.Array; ++i)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n                }");
            
            #line 112 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

            }
            
            
            #line default
            #line hidden
            this.Write("\r\n            }");
            
            #line 116 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

        }
        
            
            #line default
            #line hidden
            this.Write("\r\n        }");
            
            #line 120 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"

        
    }
    
            
            #line default
            #line hidden
            this.Write(@"
    }

    GameServer::~GameServer() {}

    void GameServer::Play(GameClient& client)
    {
        std::string line;
        std::getline(std::cin, line);
        const char* buf = line.c_str();
        int playerId = ReadNextInt<int>(buf);
        ");
            
            #line 135 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write(@" data;
        Deserialize(data, buf);
        client.InitGame(data, data.player[playerId]);
        for (;;)
        {
            std::getline(std::cin, line);
            if (line == ""EOT"")
                break;
            buf = line.c_str();
            ");
            
            #line 144 "D:\ugly\CodeGenerator\cxx\CxxImpl.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write(" turn;\r\n            Deserialize(turn, buf);\r\n            client.PlayTurn(turn, tu" +
                    "rn.player[playerId]);\r\n        }\r\n        client.Shutdown();\r\n    }\r\n}");
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
