namespace cpp scriptapi

service MIAScriptAPI {
  string MIGetTaskParam(1:string ParamName),
  void MISetTaskParam(1:string ParamName, 2:string ParamValue),
  void MILogMsg(1:string Message)
}
