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
    
    #line 1 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.TextTemplating", "14.0.0.0")]
    public partial class CsHeader : CsHeaderBase
    {
#line hidden
        /// <summary>
        /// Create the template output
        /// </summary>
        public virtual string TransformText()
        {
            this.Write("using System;\r\nusing System.Collections.Generic;\r\n\r\nnamespace ");
            
            #line 9 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.Namespace)));
            
            #line default
            #line hidden
            this.Write("\r\n{");
            
            #line 10 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

    foreach (GameConstantContainer c in CsHelper.CurrentFile.ConstantContainer)
    {
    
            
            #line default
            #line hidden
            this.Write("\r\n\r\n    public static class ");
            
            #line 16 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(c.Name)));
            
            #line default
            #line hidden
            this.Write("\r\n    {");
            
            #line 17 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

        foreach (GameConstant gc in c.Constant)
        {
            
            
            #line default
            #line hidden
            this.Write("\r\n        public const ");
            
            #line 22 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(CsHelper.GetBasicTypeName(CsHelper.Definition.GetBasicType(gc.Type))));
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 22 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(gc.Name)));
            
            #line default
            #line hidden
            this.Write(" = ");
            
            #line 22 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(gc.Value));
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 22 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

        }
        
            
            #line default
            #line hidden
            this.Write("\r\n    }");
            
            #line 26 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

    }

    foreach (GameEnum e in CsHelper.CurrentFile.Enum)
    {
    
            
            #line default
            #line hidden
            this.Write("\r\n    ");
            
            #line 33 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

    if (e.Flag)
    {
        
            
            #line default
            #line hidden
            this.Write("\r\n    [Flags]");
            
            #line 38 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

    }
    
            
            #line default
            #line hidden
            this.Write("\r\n    public enum ");
            
            #line 42 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(e.Name)));
            
            #line default
            #line hidden
            this.Write("\r\n    {");
            
            #line 43 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

        foreach (KeyValuePair<string, int> kvp in e.Value)
        {
        
            
            #line default
            #line hidden
            this.Write("\r\n        ");
            
            #line 48 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(kvp.Key)));
            
            #line default
            #line hidden
            this.Write(" = ");
            
            #line 48 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(kvp.Value));
            
            #line default
            #line hidden
            this.Write(",");
            
            #line 48 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

        }
        
            
            #line default
            #line hidden
            this.Write("\r\n    }");
            
            #line 52 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

    }
    
    foreach (GameClass c in CsHelper.CurrentFile.Class)
    {
    
            
            #line default
            #line hidden
            this.Write("\r\n\r\n    public class ");
            
            #line 60 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(c.Name)));
            
            #line default
            #line hidden
            this.Write("\r\n    {");
            
            #line 61 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

        foreach (GameConstant gc in c.Constant)
        {
            
            
            #line default
            #line hidden
            this.Write("\r\n        public const ");
            
            #line 66 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(CsHelper.GetBasicTypeName(CsHelper.Definition.GetBasicType(gc.Type))));
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 66 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(gc.Name)));
            
            #line default
            #line hidden
            this.Write(" = ");
            
            #line 66 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(gc.Value));
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 66 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

        }
        
            
            #line default
            #line hidden
            this.Write("\r\n        ");
            
            #line 70 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

        foreach (ClassMember m in c.Member)
        {
            
            
            #line default
            #line hidden
            this.Write("\r\n        public ");
            
            #line 75 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            BasicType type = CsHelper.Definition.GetBasicType(m.Type);
            if (m.Array == 1 && m.IsWeak)
            {
                
            
            #line default
            #line hidden
            this.Write("List<");
            
            #line 79 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            }
            if (type.IsBasic())
            {
                
            
            #line default
            #line hidden
            
            #line 83 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(CsHelper.GetBasicTypeName(type)));
            
            #line default
            #line hidden
            
            #line 83 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            }
            else
            {
                
            
            #line default
            #line hidden
            
            #line 87 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Type)));
            
            #line default
            #line hidden
            
            #line 87 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            }
            if (m.Array == 1 && m.IsWeak)
            {
                
            
            #line default
            #line hidden
            this.Write(">");
            
            #line 91 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            }
            else if (m.Array != 0)
            {
                
            
            #line default
            #line hidden
            this.Write("[");
            
            #line 95 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

                for (int i = 1; i < m.Array; ++i)
                {
                    
            
            #line default
            #line hidden
            this.Write(",");
            
            #line 98 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

                }
                
            
            #line default
            #line hidden
            this.Write("]");
            
            #line 100 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            }
            
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 102 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Name)));
            
            #line default
            #line hidden
            
            #line 102 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            if (m.Array == 0 && type == BasicType.Class && !m.IsWeak)
            {
                
            
            #line default
            #line hidden
            this.Write(" = new ");
            
            #line 105 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Type)));
            
            #line default
            #line hidden
            this.Write("()");
            
            #line 105 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            }
            else if (m.Array == 1 && m.IsWeak)
            {
                
            
            #line default
            #line hidden
            this.Write(" = new List<");
            
            #line 109 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Type)));
            
            #line default
            #line hidden
            this.Write(">()");
            
            #line 109 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            }
            
            
            #line default
            #line hidden
            this.Write(";");
            
            #line 111 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

        }
        
            
            #line default
            #line hidden
            this.Write("\r\n        ");
            
            #line 115 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

        foreach (ClassMethod m in c.Method)
        {
            
            
            #line default
            #line hidden
            this.Write("\r\n        public void ");
            
            #line 120 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(m.Name)));
            
            #line default
            #line hidden
            this.Write("(");
            
            #line 120 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            for (int idxParam = 0; idxParam < m.Param.Count; ++idxParam)
            {
                MethodParam a = m.Param[idxParam];
                BasicType type = CsHelper.Definition.GetBasicType(a.Type);
                if (idxParam != 0)
                {
                    
            
            #line default
            #line hidden
            this.Write(", ");
            
            #line 127 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

                }
                if (type.IsBasic())
                {
                    
            
            #line default
            #line hidden
            
            #line 131 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(CsHelper.GetBasicTypeName(type)));
            
            #line default
            #line hidden
            
            #line 131 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

                }
                else
                {
                    
            
            #line default
            #line hidden
            
            #line 135 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(a.Type)));
            
            #line default
            #line hidden
            
            #line 135 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

                }
                
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 137 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(a.Name)));
            
            #line default
            #line hidden
            
            #line 137 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            }
            
            
            #line default
            #line hidden
            this.Write(")\r\n        {\r\n            Console.WriteLine(\"");
            
            #line 141 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(m.MethodId));
            
            #line default
            #line hidden
            
            #line 141 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            for (int idxParam = 0, paramCount = m.Param.Sum(a => CsHelper.GetSerializedMemberCount(a.Type)); idxParam < paramCount; ++idxParam)
            {
                
            
            #line default
            #line hidden
            this.Write(" {");
            
            #line 144 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(idxParam));
            
            #line default
            #line hidden
            this.Write("}");
            
            #line 144 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            }
            
            
            #line default
            #line hidden
            this.Write("\"");
            
            #line 146 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            foreach (MethodParam a in m.Param)
            {
                
            
            #line default
            #line hidden
            this.Write(", ");
            
            #line 149 "D:\ugly\CodeGenerator\cs\CsHeader.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(CsHelper.GetSerializedMemberString("", a.Type, Case.LowerCamelCase.Convert(a.Name))));
            
            #line default
            #line hidden
            
            #line 149 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

            }
                
            
            #line default
            #line hidden
            this.Write(");\r\n        }");
            
            #line 152 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

        }
        
            
            #line default
            #line hidden
            this.Write("\r\n    }");
            
            #line 156 "D:\ugly\CodeGenerator\cs\CsHeader.tt"

    }
    
            
            #line default
            #line hidden
            this.Write("\r\n}");
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
    public class CsHeaderBase
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
