using System;
using System.Diagnostics;

namespace FreeMarket
{
    public static partial class GameServer
    {
        private static bool StartLocalServer(string serverPath, string commandLine)
        {
            ProcessStartInfo startInfo = new ProcessStartInfo(serverPath, commandLine);
            startInfo.UseShellExecute = false;
            startInfo.RedirectStandardOutput = true;
            startInfo.RedirectStandardInput = true;
            Process process = Process.Start(startInfo);
            if (process == null)
                return false;
            Console.SetOut(process.StandardInput);
            Console.SetIn(process.StandardOutput);
            return true;
        }
    }
}
