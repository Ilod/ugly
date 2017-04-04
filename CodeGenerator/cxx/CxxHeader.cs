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
    
    #line 1 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.TextTemplating", "14.0.0.0")]
    public partial class CxxHeader : CxxHeaderBase
    {
#line hidden
        /// <summary>
        /// Create the template output
        /// </summary>
        public virtual string TransformText()
        {
            this.Write("#pragma once\r\n#include <vector>\r\n#include <cstdint>");
            
            #line 8 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

if (CxxHelper.Server)
{
    
            
            #line default
            #line hidden
            this.Write("\r\n#include \"");
            
            #line 13 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.CurrentFile.Name)));
            
            #line default
            #line hidden
            this.Write("Private.h\"");
            
            #line 13 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

}
ISet<string> weak = new SortedSet<string>();
ISet<string> strong = new SortedSet<string>();
foreach (GameClass c in CxxHelper.CurrentFile.Class)
{
    foreach (ClassMember m in c.Member)
    {
        BasicType type = CxxHelper.Definition.GetBasicType(m.Type);
        if (type.IsBasic())
            continue;
        if (type == BasicType.Class)
        {
            if (m.IsWeak)
            {
                weak.Add(m.Type);
            }
            else
            {
                strong.Add(CxxHelper.Definition.Class[m.Type].File.Name);
            }
        }
        else if (type == BasicType.Enum)
        {
            strong.Add(CxxHelper.Definition.Enum[m.Type].File.Name);
        }
    }
    foreach (ClassMethod m in c.Method)
    {
        foreach (MethodParam a in m.Param)
        {
            BasicType type = CxxHelper.Definition.GetBasicType(a.Type);
            if (type.IsBasic())
                continue;
            if (type == BasicType.Class)
            {
                weak.Add(a.Type);
            }
            else if (type == BasicType.Enum)
            {
                strong.Add(CxxHelper.Definition.Enum[a.Type].File.Name);
            }
        }
    }
}
strong.Remove(CxxHelper.CurrentFile.Name);
foreach (string file in strong)
{
    
            
            #line default
            #line hidden
            this.Write("\r\n#include \"");
            
            #line 63 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(file)));
            
            #line default
            #line hidden
            this.Write(".h\"");
            
            #line 63 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

}

if (CxxHelper.Server)
{
    
            
            #line default
            #line hidden
            this.Write("\r\n\r\nnamespace ugly\r\n{");
            
            #line 72 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

    this.PushIndent("    ");
}

            
            #line default
            #line hidden
            this.Write("\r\nnamespace ");
            
            #line 77 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.Namespace)));
            
            #line default
            #line hidden
            this.Write("\r\n{");
            
            #line 78 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

    foreach (string s in weak)
    {
        string file = CxxHelper.Definition.Class[s].File.Name;
        if (file == CxxHelper.CurrentFile.Name)
            continue;
        if (strong.Contains(file))
            continue;
        
            
            #line default
            #line hidden
            this.Write("\r\n    struct ");
            
            #line 88 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(s)));
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 88 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

    }

    foreach (GameConstantContainer c in CxxHelper.CurrentFile.ConstantContainer)
    {
        
            
            #line default
            #line hidden
            this.Write("\r\n    namespace ");
            
            #line 95 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(c.Name)));
            
            #line default
            #line hidden
            this.Write("\r\n    {");
            
            #line 96 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

        foreach (GameConstant gc in c.Constant)
        {
            
            
            #line default
            #line hidden
            this.Write("\r\n        static const ");
            
            #line 101 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(CxxHelper.GetBasicTypeName(CxxHelper.Definition.GetBasicType(gc.Type))));
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 101 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(gc.Name)));
            
            #line default
            #line hidden
            this.Write(" = ");
            
            #line 101 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(gc.Value));
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 101 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

        }
        
            
            #line default
            #line hidden
            this.Write("\r\n    }");
            
            #line 105 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

    }


    foreach (GameEnum e in CxxHelper.CurrentFile.Enum)
    {
    
            
            #line default
            #line hidden
            this.Write("\r\n    \r\n    enum class ");
            
            #line 114 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(e.Name)));
            
            #line default
            #line hidden
            this.Write("\r\n    {");
            
            #line 115 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

        foreach (KeyValuePair<string, int> kvp in e.Value)
        {
        
            
            #line default
            #line hidden
            this.Write("        \r\n        ");
            
            #line 120 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(kvp.Key)));
            
            #line default
            #line hidden
            this.Write(" = ");
            
            #line 120 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(kvp.Value));
            
            #line default
            #line hidden
            this.Write(",");
            
            #line 120 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

        }
        
            
            #line default
            #line hidden
            this.Write("\r\n    };");
            
            #line 124 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

    }
    
    foreach (GameClass c in CxxHelper.CurrentFile.Class)
    {
    
            
            #line default
            #line hidden
            this.Write("\r\n\r\n    struct ");
            
            #line 132 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(c.Name)));
            
            #line default
            #line hidden
            this.Write("\r\n    {");
            
            #line 133 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

        foreach (ClassMember m in c.Member)
        {
            
            
            #line default
            #line hidden
            this.Write("\r\n        ");
            
            #line 138 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            for (int i = 0; i < m.Array; ++i)
            {
                
            
            #line default
            #line hidden
            this.Write("std::vector<");
            
            #line 141 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            }
            BasicType type = CxxHelper.Definition.GetBasicType(m.Type);
            if (type.IsBasic())
            {
                
            
            #line default
            #line hidden
            
            #line 146 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(CxxHelper.GetBasicTypeName(type)));
            
            #line default
            #line hidden
            
            #line 146 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            }
            else
            {
                
            
            #line default
            #line hidden
            
            #line 150 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Type)));
            
            #line default
            #line hidden
            
            #line 150 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            }
            if (m.IsWeak)
            {
                
            
            #line default
            #line hidden
            this.Write("*");
            
            #line 154 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            }
            for (int i = 0; i < m.Array; ++i)
            {
                
            
            #line default
            #line hidden
            this.Write(">");
            
            #line 158 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            }
            
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 160 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(m.Name)));
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 160 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

        }

        if (CxxHelper.Server)
        {
            
            
            #line default
            #line hidden
            this.Write("\r\n        ");
            
            #line 167 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(c.Name)));
            
            #line default
            #line hidden
            this.Write("Private additionalData;");
            
            #line 167 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

        }
        
            
            #line default
            #line hidden
            this.Write("        \r\n\r\n        ");
            
            #line 172 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

        foreach (GameConstant gc in c.Constant)
        {
            
            
            #line default
            #line hidden
            this.Write("\r\n        static const ");
            
            #line 177 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(CxxHelper.GetBasicTypeName(CxxHelper.Definition.GetBasicType(gc.Type))));
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 177 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(gc.Name)));
            
            #line default
            #line hidden
            this.Write(" = ");
            
            #line 177 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(gc.Value));
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 177 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

        }
        
            
            #line default
            #line hidden
            this.Write("\r\n\r\n        ");
            
            #line 182 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(c.Name)));
            
            #line default
            #line hidden
            this.Write("();\r\n        ");
            
            #line 183 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

        foreach (ClassMethod m in c.Method)
        {
            if (CxxHelper.Server)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n        bool");
            
            #line 190 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            }
            else
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n        void");
            
            #line 196 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            }
            
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 198 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Name)));
            
            #line default
            #line hidden
            this.Write("(");
            
            #line 198 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            if (CxxHelper.Server)
            {
                
            
            #line default
            #line hidden
            this.Write("struct ");
            
            #line 201 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write("& gameSetup, struct ");
            
            #line 201 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.PlayerSetup)));
            
            #line default
            #line hidden
            this.Write("& playerSetup, struct ");
            
            #line 201 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write("& gameState, struct ");
            
            #line 201 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.PlayerState)));
            
            #line default
            #line hidden
            this.Write("& playerState");
            
            #line 201 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(m.Param.Any() ? ", " : ""));
            
            #line default
            #line hidden
            
            #line 201 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            }
            for (int idxParam = 0; idxParam < m.Param.Count; ++idxParam)
            {
                MethodParam a = m.Param[idxParam];
                BasicType type = CxxHelper.Definition.GetBasicType(a.Type);
                if (idxParam != 0)
                {
                    
            
            #line default
            #line hidden
            this.Write(", ");
            
            #line 209 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

                }
                if (type == BasicType.Class && !CxxHelper.Server)
                {
                    
            
            #line default
            #line hidden
            this.Write("const ");
            
            #line 213 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

                }
                if (type.IsBasic())
                {
                    
            
            #line default
            #line hidden
            
            #line 217 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(CxxHelper.GetBasicTypeName(type)));
            
            #line default
            #line hidden
            
            #line 217 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

                }
                else
                {
                    
            
            #line default
            #line hidden
            
            #line 221 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(a.Type)));
            
            #line default
            #line hidden
            
            #line 221 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

                }
                if (type == BasicType.Class)
                {
                    
            
            #line default
            #line hidden
            this.Write("&");
            
            #line 225 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

                }
                
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 227 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(a.Name)));
            
            #line default
            #line hidden
            
            #line 227 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            }
            if (CxxHelper.Server)
            {
                
            
            #line default
            #line hidden
            this.Write(", const std::string& orderStr");
            
            #line 231 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            }
            
            
            #line default
            #line hidden
            this.Write(");");
            
            #line 233 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

        }
        if (CxxHelper.Server)
        {
            if (c.ConditionMethod.Any())
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n");
            
            #line 241 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            }
            foreach (Tuple<string, int> m in c.ConditionMethod)
            {
                
            
            #line default
            #line hidden
            this.Write("\r\n        bool ");
            
            #line 247 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Item1)));
            
            #line default
            #line hidden
            this.Write("(struct ");
            
            #line 247 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write("& gameSetup, struct ");
            
            #line 247 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.PlayerSetup)));
            
            #line default
            #line hidden
            this.Write("& playerSetup, struct ");
            
            #line 247 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write("& gameState, struct ");
            
            #line 247 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CxxHelper.Definition.Config.PlayerState)));
            
            #line default
            #line hidden
            this.Write("& playerState");
            
            #line 247 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

                for (int i = 0; i < m.Item2; ++i)
                {
                    
            
            #line default
            #line hidden
            this.Write(", int idx");
            
            #line 250 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(i));
            
            #line default
            #line hidden
            
            #line 250 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

                }
                
            
            #line default
            #line hidden
            this.Write(");");
            
            #line 252 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

            }
        }
        
            
            #line default
            #line hidden
            this.Write("\r\n    };");
            
            #line 257 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

    }
    
            
            #line default
            #line hidden
            this.Write("\r\n}");
            
            #line 261 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

if (CxxHelper.Server)
{
    this.PopIndent();
    
            
            #line default
            #line hidden
            this.Write("\r\n}");
            
            #line 267 "D:\ugly\CodeGenerator\cxx\CxxHeader.tt"

}

            
            #line default
            #line hidden
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
    public class CxxHeaderBase
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
