
using System;
using System.IO;
using System.Management.Automation;
using System.Management.Automation.Runspaces;
//using System.Text;
//using System.Threading.Tasks;
using Thrift.Transport;
using Thrift.Protocol;
using System.Reflection;
//using MIAScriptAPI;

namespace PSHostApp
{
    class PSHostApp
    {
        static void Execute(string source, int port) {
            InitialSessionState iss = InitialSessionState.CreateDefault();

            TTransport trans;
            trans = new TSocket("localhost", port);
            trans = new TBufferedTransport(trans);
            trans.Open();

            TProtocol Protocol = new TBinaryProtocol(trans, true, true);

            MIAScriptAPI.Client miaclient = new MIAScriptAPI.Client(Protocol);

            SessionStateVariableEntry ssveItem = new SessionStateVariableEntry("miaclient", miaclient, "Client to talk to MOVEit Automation");
            iss.Variables.Add(ssveItem);

            PowerShell ps = PowerShell.Create(iss);
            System.Collections.ObjectModel.Collection<System.Management.Automation.PSObject> psOutput = null;
            try {
                psOutput = ps.AddScript(source).Invoke();
                foreach(PSObject psobj in psOutput) {
                    Console.WriteLine("PS: " + psobj.ToString());
                }
            } catch(Exception e) {
                Console.Write("PS exception: " + e.Message);
            }
        }

        static void Main(string[] args) {
            int port = 9090;
            string source = "";
            if (args.Length > 0) {
                string srcFilename = args[0];
                source = File.ReadAllText(srcFilename);
                //Console.WriteLine("Read {0} chars of source from {1}", source.Length, srcFilename);
            }
            Execute(source, port);
        }
    }
}
