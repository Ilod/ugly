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
    
    #line 1 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.TextTemplating", "14.0.0.0")]
    public partial class CsInterface : CsInterfaceBase
    {
#line hidden
        /// <summary>
        /// Create the template output
        /// </summary>
        public virtual string TransformText()
        {
            this.Write("using System;\r\nusing System.IO;\r\nusing System.Collections.Generic;\r\nusing System." +
                    "Linq;\r\n\r\nnamespace ");
            
            #line 11 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.Namespace)));
            
            #line default
            #line hidden
            this.Write("\r\n{\r\n    public interface GameClient\r\n    {\r\n        void InitGame(");
            
            #line 15 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 15 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(CsHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write(", ");
            
            #line 15 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.PlayerSetup)));
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 15 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(CsHelper.Definition.Config.PlayerSetup)));
            
            #line default
            #line hidden
            this.Write(");\r\n        void PlayTurn(");
            
            #line 16 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 16 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(CsHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write(", ");
            
            #line 16 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.PlayerState)));
            
            #line default
            #line hidden
            this.Write(" ");
            
            #line 16 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.LowerCamelCase.Convert(CsHelper.Definition.Config.PlayerState)));
            
            #line default
            #line hidden
            this.Write(");\r\n        void Cleanup();\r\n    }\r\n\r\n    public static partial class GameServer\r" +
                    "\n    {\r\n        public static void Play(GameClient client)\r\n        {\r\n         " +
                    "   Tuple<");
            
            #line 24 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameSetup)));
            
            #line default
            #line hidden
            this.Write(", ");
            
            #line 24 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.PlayerSetup)));
            
            #line default
            #line hidden
            this.Write("> setup = ReadSetup();\r\n            int playerId = setup.Item2.Id;\r\n            c" +
                    "lient.InitGame(setup.Item1, setup.Item2);\r\n            ");
            
            #line 27 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.GameState)));
            
            #line default
            #line hidden
            this.Write(@" turn = null;
            while ((turn = ReadTurn()) != null)
            {
                client.PlayTurn(turn, turn.Player[playerId]);
            }
            client.Cleanup();
            Console.WriteLine(""EOT"");
        }
        
        public static IList<Tuple<int, int>> PlayLocalServer(GameClient client, string serverPath, IList<string> otherPlayers = null, string game = """);
            
            #line 36 "D:\ugly\CodeGenerator\cs\CsInterface.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(Case.CamelCase.Convert(CsHelper.Definition.Config.Namespace)));
            
            #line default
            #line hidden
            this.Write(@""", string serverArgs = """")
        {
            return PlayLocalServerCommandLine(client, serverPath, string.Format(""-game \""{0}\"" {1} {2}"", game, string.Join("" "", (otherPlayers ?? Enumerable.Empty<string>()).Select(player => string.Format(""-player \""{0}\"""", player))), serverArgs));
        }

        public static IList<Tuple<int, int>> PlayLocalServerCommandLine(GameClient client, string serverPath, string commandLine)
        {
            List<Tuple<int, int>> results = new List<Tuple<int, int>>();
            if (!StartLocalServer(serverPath, commandLine))
                return results;
            Play(client);
            string[] tokens = Console.ReadLine().Split(new char[] { ' ' });
            for (int i = 0; i < tokens.Length / 2; ++i)
                results.Add(Tuple.Create(int.Parse(tokens[i*2]), int.Parse(tokens[i*2+1])));
            return results;
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
    public class CsInterfaceBase
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
