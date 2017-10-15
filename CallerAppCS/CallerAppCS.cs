using System;
using System.IO;
using Thrift.Transport;
using Thrift.Protocol;
using System.Reflection;
using System.CodeDom.Compiler;
using Microsoft.CSharp;
using Microsoft.VisualBasic;
//using MIAScriptAPI;

// This is the official PoC for VB.NET scripting.
// It compiles and runs VB.NET source, and provides an MIxxx API whose implementation
// is done in a separate backend process.
// Mark Riordan  Oct 2017

namespace CallerAppCS
{
    public class CallerAppCS
    {
        /// <summary>
        /// No longer used.
        /// </summary>
        /// <param name="port"></param>
        static void Execute(int port) {
            try {
                Console.WriteLine("Entered CallerAppCS");
                TTransport trans;
                trans = new TSocket("localhost", port);
                //trans = new TFramedTransport(trans);
                trans = new TBufferedTransport(trans);
                trans.Open();

                TProtocol Protocol = new TBinaryProtocol(trans, true, true);

                MIAScriptAPI.Client miaclient = new MIAScriptAPI.Client(Protocol);
                Console.WriteLine("Instantiated MIAScriptAPI.Client");

                miaclient.MILogMsg("Greetings from CallerAppCS");

                miaclient.MISetTaskParam("lang", "C#");

                string retrievedLang = miaclient.MIGetTaskParam("lang");
                Console.WriteLine("MIGetTaskParam(\"lang\") returned " + retrievedLang);
                miaclient.MILogMsg("MIGetTaskParam(\"lang\") returned " + retrievedLang);

                //                TMultiplexedProtocol multiplex;

                //multiplex = new TMultiplexedProtocol(Protocol, Constants.NAME_BENCHMARKSERVICE);
                //BenchmarkService.Iface bench = new BenchmarkService.Client(multiplex);

                //multiplex = new TMultiplexedProtocol(Protocol, Constants.NAME_AGGR);
                //Aggr.Iface aggr = new Aggr.Client(multiplex);

                //for (sbyte i = 1; 10 >= i; ++i) {
                //    aggr.addValue(bench.fibonacci(i));
                //}

                //foreach (int k in aggr.getValues()) {
                //    Console.Write(k.ToString() + " ");
                //    Console.WriteLine("");
                //}
                Console.WriteLine("About to close transport");
                trans.Close();
            }
            catch (Exception e) {
                Console.WriteLine(e.Message);
            }
        }

        private static void CompileAndExecute(string sourceCode, string lang, int port) {
            //ICodeCompiler loCompiler = new CSharpCodeProvider().CreateCompiler();
            if(null==lang || lang.Length == 0) {
                lang = "VisualBasic";
            }
            CodeDomProvider provider = CodeDomProvider.CreateProvider(lang);
            //ICodeCompiler loCompiler = new Microsoft.VisualBasic.VBCodeProvider().CreateCompiler();
            //provider.CompileAssemblyFromSource()
            ICodeCompiler loCompiler = provider.CreateCompiler();

            CompilerParameters loParameters = new CompilerParameters();

            // *** Start by adding any referenced assemblies
            loParameters.ReferencedAssemblies.Add("System.dll");
            loParameters.ReferencedAssemblies.Add("System.Core.dll");
            loParameters.ReferencedAssemblies.Add("mscorlib.dll");
            //loParameters.ReferencedAssemblies.Add("mscoree.dll");
            loParameters.ReferencedAssemblies.Add("System.Web.dll");
            loParameters.ReferencedAssemblies.Add("Newtonsoft.Json.dll");
            loParameters.ReferencedAssemblies.Add(@"C:\dist\thrift-0.10.0\lib\csharp\src\bin\Debug\thrift.dll");
            loParameters.ReferencedAssemblies.Add(@"C:\tmp\moveit\node-thrift-poc\MIANETClient\obj\Debug\MIANETClient.dll");

            //loParameters.ReferencedAssemblies.Add("mscoree.dll");
            //loParameters.ReferencedAssemblies.Add("mscoreei.dll");

            // *** Load the resulting assembly into memory
            loParameters.GenerateInMemory = false;

            // *** Now compile the whole thing
            CompilerResults loCompiled = loCompiler.CompileAssemblyFromSource(loParameters, sourceCode);

            if (loCompiled.Errors.HasErrors) {
                string lcErrorMsg = "";
                lcErrorMsg = loCompiled.Errors.Count.ToString() + " Errors:";
                for (int x = 0; x < loCompiled.Errors.Count; x++)
                    lcErrorMsg = lcErrorMsg + "\r\nLine: " +
                                 loCompiled.Errors[x].Line.ToString() + " - " +
                                 loCompiled.Errors[x].ErrorText;

                Console.WriteLine(lcErrorMsg + "\r\n\r\n" /* + sourceCode */);
                return;
            }

            Assembly loAssembly = loCompiled.CompiledAssembly;
            // *** Retrieve an obj ref – generic type only
            object loObject = loAssembly.CreateInstance("Class1");
            if (loObject == null) {
                Console.WriteLine("Couldn't load class.");
                return;
            }

            MIAScriptAPI.Client miaclient = MIAScriptAPI.CreateMIAScriptAPI(port);

            object[] loCodeParms = new object[1];
            loCodeParms[0] = miaclient;

            try {
                object loResult = loObject.GetType().InvokeMember(
                                 "Sub1", BindingFlags.InvokeMethod,
                                 null, loObject, loCodeParms);

                // loResult will be null if we are calling a Sub rather than a Function.
                //DateTime ltNow = (DateTime)loResult;
                //Console.WriteLine("Method Call Result:\r\n\r\n" + loResult.ToString());
            } catch (Exception loError) {
                Console.WriteLine("Caught exception invoking method: " + loError.Message);
            }
        }

        static void Main(string[] args) {
            int port = 9090;
            //Console.WriteLine("CallerAppCS here");
            //Console.ReadLine();
            //if (args.Length > 0) {
            //    port = ushort.Parse(args[0]);
            //}
            //Execute(port);
            string source = 
                  "Imports System\r\n"
                + "Imports System.IO\r\n"
                + "\r\n"
                + "  Public Class Class1\r\n"
                + "    Public Sub Sub1(obj)\r\n"
                + "      Console.WriteLine(\"This is from VB\")\r\n"
                + "    End Sub\r\n"
                + "  End Class\r\n"
                ;

            if(args.Length > 0) {
                string srcFilename = args[0];
                source = File.ReadAllText(srcFilename);
                //Console.WriteLine("Read {0} chars of source from {1}", source.Length, srcFilename);
            }

            CompileAndExecute(source, "VisualBasic", port);
            Console.WriteLine("done.");
        }

    }
}
