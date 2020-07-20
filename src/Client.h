// Copyright 2014 SAP AG.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http: //www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific
// language governing permissions and limitations under the License.

#ifndef NodeRfc_Client_H
#define NodeRfc_Client_H

#include <tuple>
#include <uv.h>
namespace node_rfc
{
    extern Napi::Env __env;

    class Pool;
    void checkConnectionParams(Napi::Object clientParamsObject, ConnectionParamsStruct *clientParams);
    void checkClientOptions(Napi::Object clientOptionsObject, ClientOptionsStruct *clientOptions);

    typedef std::pair<Napi::Value, Napi::Value> WrapResultType;

    class Client : public Napi::ObjectWrap<Client>
    {
    public:
        friend class Pool;
        friend class AcquireAsync;
        friend class ReleaseAsync;
        friend class OpenAsync;
        friend class CheckPoolAsync;
        friend class CloseAsync;
        friend class ResetServerAsync;
        friend class PingAsync;
        friend class PrepareAsync;
        friend class InvokeAsync;
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        Client(const Napi::CallbackInfo &info);
        ~Client(void);

    private:
        static Napi::Object NewInstance(Napi::Env env);
        Napi::Value IdGetter(const Napi::CallbackInfo &info);
        Napi::Value AliveGetter(const Napi::CallbackInfo &info);
        Napi::Value ConfigGetter(const Napi::CallbackInfo &info);
        Napi::Value ConnectionHandleGetter(const Napi::CallbackInfo &info);
        Napi::Value PoolIdGetter(const Napi::CallbackInfo &info);
        Napi::ObjectReference clientParamsRef;
        Napi::ObjectReference clientOptionsRef;
        Napi::Value connectionClosedError(std::string suffix);

        Napi::Value connectionCheck(RFC_ERROR_INFO *errorInfo);
        Napi::Value ConnectionInfo(const Napi::CallbackInfo &info);
        Napi::Value Release(const Napi::CallbackInfo &info);
        Napi::Value Open(const Napi::CallbackInfo &info);
        Napi::Value Close(const Napi::CallbackInfo &info);
        Napi::Value ResetServerContext(const Napi::CallbackInfo &info);
        Napi::Value Ping(const Napi::CallbackInfo &info);
        Napi::Value Invoke(const Napi::CallbackInfo &info);

        SAP_UC *fillString(std::string str);
        Napi::Value fillFunctionParameter(RFC_FUNCTION_DESC_HANDLE functionDescHandle, RFC_FUNCTION_HANDLE functionHandle, Napi::String name, Napi::Value value);
        Napi::Value fillStructure(RFC_STRUCTURE_HANDLE structHandle, RFC_TYPE_DESC_HANDLE functionDescHandle, SAP_UC *cName, Napi::Value value);
        Napi::Value fillVariable(RFCTYPE typ, RFC_FUNCTION_HANDLE functionHandle, SAP_UC *cName, Napi::Value value, RFC_TYPE_DESC_HANDLE functionDescHandle);

        WrapResultType wrapStructure(RFC_TYPE_DESC_HANDLE typeDesc, RFC_STRUCTURE_HANDLE structHandle);
        WrapResultType wrapVariable(RFCTYPE typ, RFC_FUNCTION_HANDLE functionHandle, SAP_UC *cName, uint_t cLen, RFC_TYPE_DESC_HANDLE typeDesc);
        WrapResultType wrapResult(RFC_FUNCTION_DESC_HANDLE functionDescHandle, RFC_FUNCTION_HANDLE functionHandle);

        RfmErrorPath errorPath;

        void init(Napi::Env env)
        {
            node_rfc::__env = env;
            id = Client::_id++;

            pool = NULL;
            connectionHandle = NULL;

            uv_sem_init(&invocationMutex, 1);

            destructor_call = false;
        };

        static uint_t _id;
        uint_t id;
        Pool *pool;
        RFC_CONNECTION_HANDLE connectionHandle;

        ConnectionParamsStruct client_params;
        ClientOptionsStruct client_options;

        void LockMutex();
        void UnlockMutex();
        uv_sem_t invocationMutex;

        bool destructor_call;
    };

} // namespace node_rfc

#endif
