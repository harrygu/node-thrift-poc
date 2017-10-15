using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using Thrift;
using Thrift.Collections;
using System.Runtime.Serialization;
using Thrift.Protocol;
using Thrift.Transport;

// This code, used by CallerAppCS, extends the auto-generated code in MIAScriptAPI.cs
// to provide a way to create a client object that uses that code.

public partial class MIAScriptAPI
{
    protected TTransport transport;

    public static MIAScriptAPI.Client CreateMIAScriptAPI(int port) {
        TTransport trans;
        trans = new TSocket("localhost", port);
        trans = new TBufferedTransport(trans);
        // Note:  We need a way of closing the transport when the script is done.  
        // This is done via trans.Close()
        // which should be accessible via:
        // miaClient.InputProtocol.Transport.Close();
        trans.Open();

        TProtocol Protocol = new TBinaryProtocol(trans, true, true);

        MIAScriptAPI.Client miaClient = new MIAScriptAPI.Client(Protocol);

        return miaClient;
    }
}