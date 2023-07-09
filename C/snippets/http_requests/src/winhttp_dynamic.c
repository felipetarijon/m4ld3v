/*
 * This snippet was taken from  https://gist.githubusercontent.com/s0d0ma/38c809cfc40c03fec5f39f15c149b07e/raw/4de559dd6d7b946816944ec9daac79a5bb18fc45/winhttp-example.c
 * It uses WinHTTP by dynamically loading it.
 * To build we don't need to link the winhttp.
 * Simply run: C:\mingw32\bin\gcc -s -o winhttp .\src\winhttp.c
*/

#ifndef UNICODE
    #define UNICODE
    #define _UNICODE
#endif // UNICODE
#include <windows.h>
#include <wininet.h>
#include <wchar.h>
#include <stdio.h>

struct responseGet
{
    LPCWSTR header;
    LPSTR Response;
    DWORD len_header;
    DWORD len_response;
};

struct responsePOST
{
    LPCWSTR header;
    LPSTR Response;
    DWORD len_header;
    DWORD len_response;
};
/*
        struct responseGet * rep = Get(
                                 L"C:\\Windows\\System32\\winhttp.dll",
                                 L"www.google.com",
                                 (WORD) 80,
                                 L"/",
                                 L"Accept-Language:en-US,en;q=0.5\r\n");

*/
struct responseGet * Get(wchar_t * pt_dll, const wchar_t * host, WORD puerto, wchar_t * uri);

/*
    struct responsePOST * rep = Post(
                                 L"C:\\Windows\\System32\\winhttp.dll",
                                 L"192.168.0.22",
                                 (WORD) 80,
                                 L"/path",
                                 "datapost=pkpkkpkp");
*/
struct responsePOST * Post(wchar_t * pt_dll, const wchar_t * host, WORD puerto, wchar_t * uri, char * postData);

struct responseGet * Get(wchar_t * pt_dll, const wchar_t * host, WORD puerto, wchar_t * uri)
{
    struct responseGet * respuesta = malloc(sizeof(struct responseGet));
    // ptr to Function = WinHttpOpen()
    typedef HINTERNET(WINAPI * ptrWHTTPopen)(LPCWSTR, DWORD,LPCWSTR,LPCWSTR,DWORD);
    // ptr to Function = WinHttpConnect()
    typedef HINTERNET(WINAPI * ptrHttpConnect)(HINTERNET, LPCWSTR, INTERNET_PORT, DWORD);
    // ptr to Function = WinHttpOpenRequest()
    typedef HINTERNET(WINAPI * ptrHttpRequest)(HINTERNET,LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,DWORD);
    // ptr to Function = WinHttpCloseHandle()
    typedef BOOL(WINAPI * ptrWHTTPCloseHandle)(HINTERNET);
    // ptr to Function = WinHttpSendRequest()
    typedef BOOL(WINAPI * ptrHttpSendReq)(HINTERNET, LPCWSTR,DWORD,LPVOID,DWORD,DWORD,DWORD_PTR);
    // ptr to Function = WinHttpReceiveRespose()
    typedef BOOL(WINAPI * ptrHttpRecvResp)(HINTERNET,LPVOID);
    // ptr to Function = WinHttpQueryDataAvailable
    typedef BOOL(WINAPI * ptrHttpQueryAvailableD)(HINTERNET,LPDWORD);
    // ptr to Function = WinHttpReadData()
    typedef BOOL(WINAPI * ptrHttpReadData)(HINTERNET,LPVOID,DWORD,LPDWORD);
    // ptr to Function = WinHttpQueryHeaders()
    typedef BOOL(WINAPI * ptrHttpHeaderQ)(HINTERNET,DWORD,LPCWSTR,LPVOID,LPDWORD,LPDWORD);

    // Cargar libreria del path creado
    HINSTANCE LdllHttp = LoadLibrary(pt_dll);

    if(LdllHttp == NULL) return (struct responseGet *) NULL;

    //WinHttpOpen(L"user-agent",t_acceso,proxyname,proxybypass,flags)
    ptrWHTTPopen WinHttpOpen = (ptrWHTTPopen) GetProcAddress(LdllHttp , "WinHttpOpen");
    //WinHttpCloseHandle(HINTERNET_CONEXION)
    ptrWHTTPCloseHandle WinHttpCloseHandle = (ptrWHTTPCloseHandle) GetProcAddress(LdllHttp , "WinHttpCloseHandle");
    //WinHttpConnect(Hsession,L"www.porn.com",(WORD)80,0)
    ptrHttpConnect WinHttpConnect = (ptrHttpConnect) GetProcAddress(LdllHttp,"WinHttpConnect");
    //WinHttpOpenRequest(Hconect,L"GET",ObjectName,VersionHTTP,Refer,AceeptTypes,Flags)
    ptrHttpRequest WinHttpOpenRequest = (ptrHttpRequest) GetProcAddress(LdllHttp,"WinHttpOpenRequest");
    //WinHttpSendRequest(hRequest,Headers,Optional,OptionalLeng,TotalLength,Context)
    ptrHttpSendReq WinHttpSendRequest = (ptrHttpSendReq) GetProcAddress(LdllHttp,"WinHttpSendRequest");
    //WinHttpReceiveRespose(HINTERNET_HRequest, LPVOID)
    ptrHttpRecvResp WinHttpReceiveResponse = (ptrHttpRecvResp) GetProcAddress(LdllHttp,"WinHttpReceiveResponse");
    //WinHttpQueryDataAvailable(HINTERNET_hRespose,LPDWORD)
    ptrHttpQueryAvailableD WinHttpQueryDataAvailable = (ptrHttpQueryAvailableD) GetProcAddress(LdllHttp,"WinHttpQueryDataAvailable");
    //WinHttpReadData(hRequest,LPVOID, DWORD,LPDWORD)
    ptrHttpReadData WinHttpReadData = (ptrHttpReadData) GetProcAddress(LdllHttp,"WinHttpReadData");
    //WinHttpQueryHeaders(HINTERNET,DWORD,LPCWSTR,LPVOID,LPDWORD,LPDWORD)
    ptrHttpHeaderQ WinHttpQueryHeaders = (ptrHttpHeaderQ) GetProcAddress(LdllHttp,"WinHttpQueryHeaders");

    if( WinHttpOpen               == NULL || WinHttpCloseHandle  == NULL ||
        WinHttpConnect            == NULL || WinHttpOpenRequest  == NULL ||
        WinHttpSendRequest        == NULL || WinHttpReadData     == NULL ||
        WinHttpQueryDataAvailable == NULL || WinHttpQueryHeaders == NULL ||
        WinHttpReceiveResponse    == NULL
        )
            return (struct responseGet *) NULL;

    // Realizar peticiones

    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;

    hSession = WinHttpOpen(L"FuckAll/6.6(X11;Win$ucks x84_64;rv:66.6)",1,NULL,NULL,0);
    if(hSession == NULL) return (struct responseGet *) NULL;

    hConnect = WinHttpConnect(hSession,host,puerto,0);
    if(hConnect == NULL) return (struct responseGet *) NULL;

    hRequest = WinHttpOpenRequest(hConnect,L"GET",uri,NULL,NULL,NULL,0);
    if(hRequest == NULL) return (struct responseGet *) NULL;


    BOOL bResult = WinHttpSendRequest(hRequest, NULL,0,NULL,0,0,0);
    if(bResult == FALSE) return (struct responseGet *) NULL;

    bResult = WinHttpReceiveResponse(hRequest,NULL);

    if(bResult)
    {

        /*Capturando HEADER*/
        DWORD SizeHeaders = 0;
        WinHttpQueryHeaders(hRequest,22,NULL,NULL,&SizeHeaders,NULL);
        if( GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            respuesta->header = calloc(SizeHeaders/sizeof(WCHAR),sizeof(WCHAR));
            WinHttpQueryHeaders(hRequest,22,NULL,(LPVOID) respuesta->header,&SizeHeaders,NULL);
        }

        respuesta->len_header= (DWORD) SizeHeaders/sizeof(WCHAR);

        DWORD sizeResp, downloaded = 0;
        LPSTR outContent;
        LPSTR data = (char*) calloc(10000000,sizeof(char));
        respuesta->len_response = 0;

        do
        {
            sizeResp = 0;

            if( !WinHttpQueryDataAvailable( hRequest, &sizeResp))
                return (struct responseGet *) NULL;

            outContent = (char *) malloc(sizeResp+1);
            if(!outContent)
            {
                return (struct responseGet *) NULL;
            }
            else
            {
                ZeroMemory(outContent,sizeResp+1);
                if( !WinHttpReadData(hRequest, (LPVOID)outContent, sizeResp, &downloaded) )
                    return (struct responseGet *) NULL;
                else
                {
                    if(strlen(outContent) != 0)
                    {
                        strcat(data,outContent);

                    }
                }
            }



        }while(sizeResp > 0);
        respuesta->Response =(char *) calloc(strlen(data), sizeof(data));
        strncpy(respuesta->Response,data,strlen(data));
        respuesta->len_response = strlen(data);

        free(data);
    }

    // Cerrar WinHttpCloseHandle(allshit);
    WinHttpCloseHandle(hSession);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hRequest);

    //liberar funciones
    free(WinHttpOpen);
    free(WinHttpCloseHandle);
    free(WinHttpConnect);
    free(WinHttpOpenRequest);
    free(WinHttpSendRequest) ;
    free(WinHttpReceiveResponse);
    free(WinHttpQueryDataAvailable);
    free(WinHttpReadData);
    free(WinHttpQueryHeaders);

    // liberar liberia
    FreeLibrary(LdllHttp);

    return respuesta;
}

// Funcion POST

struct responsePOST * Post(wchar_t * pt_dll, const wchar_t * host, WORD puerto, wchar_t * uri,char * postData)
{
    struct responsePOST * respuesta = malloc(sizeof(struct responseGet));
    // ptr to Function = WinHttpOpen()
    typedef HINTERNET(WINAPI * ptrWHTTPopen)(LPCWSTR, DWORD,LPCWSTR,LPCWSTR,DWORD);
    // ptr to Function = WinHttpConnect()
    typedef HINTERNET(WINAPI * ptrHttpConnect)(HINTERNET, LPCWSTR, INTERNET_PORT, DWORD);
    // ptr to Function = WinHttpOpenRequest()
    typedef HINTERNET(WINAPI * ptrHttpRequest)(HINTERNET,LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,DWORD);
    // ptr to Function = WinHttpCloseHandle()
    typedef BOOL(WINAPI * ptrWHTTPCloseHandle)(HINTERNET);
    // ptr to Function = WinHttpSendRequest()
    typedef BOOL(WINAPI * ptrHttpSendReq)(HINTERNET, LPCWSTR,DWORD,LPVOID,DWORD,DWORD,DWORD_PTR);
    // ptr to Function = WinHttpReceiveRespose()
    typedef BOOL(WINAPI * ptrHttpRecvResp)(HINTERNET,LPVOID);
    // ptr to Function = WinHttpQueryDataAvailable
    typedef BOOL(WINAPI * ptrHttpQueryAvailableD)(HINTERNET,LPDWORD);
    // ptr to Function = WinHttpReadData()
    typedef BOOL(WINAPI * ptrHttpReadData)(HINTERNET,LPVOID,DWORD,LPDWORD);
    // ptr to Function = WinHttpQueryHeaders()
    typedef BOOL(WINAPI * ptrHttpHeaderQ)(HINTERNET,DWORD,LPCWSTR,LPVOID,LPDWORD,LPDWORD);

    // Cargar libreria del path creado
    HINSTANCE LdllHttp = LoadLibrary(pt_dll);

    if(LdllHttp == NULL) return (struct responsePOST *) NULL;

    //WinHttpOpen(L"user-agent",t_acceso,proxyname,proxybypass,flags)
    ptrWHTTPopen WinHttpOpen = (ptrWHTTPopen) GetProcAddress(LdllHttp , "WinHttpOpen");
    //WinHttpCloseHandle(HINTERNET_CONEXION)
    ptrWHTTPCloseHandle WinHttpCloseHandle = (ptrWHTTPCloseHandle) GetProcAddress(LdllHttp , "WinHttpCloseHandle");
    //WinHttpConnect(Hsession,L"www.porn.com",(WORD)80,0)
    ptrHttpConnect WinHttpConnect = (ptrHttpConnect) GetProcAddress(LdllHttp,"WinHttpConnect");
    //WinHttpOpenRequest(Hconect,L"GET",ObjectName,VersionHTTP,Refer,AceeptTypes,Flags)
    ptrHttpRequest WinHttpOpenRequest = (ptrHttpRequest) GetProcAddress(LdllHttp,"WinHttpOpenRequest");
    //WinHttpSendRequest(hRequest,Headers,Optional,OptionalLeng,TotalLength,Context)
    ptrHttpSendReq WinHttpSendRequest = (ptrHttpSendReq) GetProcAddress(LdllHttp,"WinHttpSendRequest");
    //WinHttpReceiveRespose(HINTERNET_HRequest, LPVOID)
    ptrHttpRecvResp WinHttpReceiveResponse = (ptrHttpRecvResp) GetProcAddress(LdllHttp,"WinHttpReceiveResponse");
    //WinHttpQueryDataAvailable(HINTERNET_hRespose,LPDWORD)
    ptrHttpQueryAvailableD WinHttpQueryDataAvailable = (ptrHttpQueryAvailableD) GetProcAddress(LdllHttp,"WinHttpQueryDataAvailable");
    //WinHttpReadData(hRequest,LPVOID, DWORD,LPDWORD)
    ptrHttpReadData WinHttpReadData = (ptrHttpReadData) GetProcAddress(LdllHttp,"WinHttpReadData");
    //WinHttpQueryHeaders(HINTERNET,DWORD,LPCWSTR,LPVOID,LPDWORD,LPDWORD)
    ptrHttpHeaderQ WinHttpQueryHeaders = (ptrHttpHeaderQ) GetProcAddress(LdllHttp,"WinHttpQueryHeaders");

    if( WinHttpOpen               == NULL || WinHttpCloseHandle  == NULL ||
        WinHttpConnect            == NULL || WinHttpOpenRequest  == NULL ||
        WinHttpSendRequest        == NULL || WinHttpReadData     == NULL ||
        WinHttpQueryDataAvailable == NULL || WinHttpQueryHeaders == NULL ||
        WinHttpReceiveResponse    == NULL
        )
            return (struct responsePOST *) NULL;

    // Realizar peticiones

    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;

    hSession = WinHttpOpen(L"FuckAll/6.6(X11;Win$ucks x84_64;rv:66.6)",1,NULL,NULL,0);
    if(hSession == NULL) return (struct responsePOST *) NULL;

    hConnect = WinHttpConnect(hSession,host,puerto,0);
    if(hConnect == NULL) return (struct responsePOST *) NULL;

    hRequest = WinHttpOpenRequest(
                                  hConnect,
                                  L"POST",
                                  uri,
                                  NULL,
                                  NULL,
                                  NULL,
                                  0);
    if(hRequest == NULL) return (struct responsePOST *) NULL;


    BOOL bResult = WinHttpSendRequest(hRequest,
                                      L"Content-Type: application/x-www-form-urlencoded\r\n",
                                      -1,
                                      (LPVOID)postData,
                                      strlen(postData),
                                      strlen(postData),
                                      0);

    if(bResult == FALSE) return (struct responsePOST *) NULL;

    bResult = WinHttpReceiveResponse(hRequest,NULL);

    if(bResult)
    {

        /*Capturando HEADER*/
        DWORD SizeHeaders = 0;
        WinHttpQueryHeaders(hRequest,22,NULL,NULL,&SizeHeaders,NULL);
        if( GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            respuesta->header = calloc(SizeHeaders/sizeof(WCHAR),sizeof(WCHAR));
            WinHttpQueryHeaders(hRequest,22,NULL,(LPVOID) respuesta->header,&SizeHeaders,NULL);
        }

        respuesta->len_header= (DWORD) SizeHeaders/sizeof(WCHAR);

        DWORD sizeResp, downloaded = 0;
        LPSTR outContent;
        LPSTR data = (char*) calloc(10000000,sizeof(char));
        respuesta->len_response = 0;

        do
        {
            sizeResp = 0;

            if( !WinHttpQueryDataAvailable( hRequest, &sizeResp))
                return (struct responsePOST *) NULL;

            outContent = (char *) malloc(sizeResp+1);
            if(!outContent)
            {
                return (struct responsePOST *) NULL;
            }
            else
            {
                ZeroMemory(outContent,sizeResp+1);
                if( !WinHttpReadData(hRequest, (LPVOID)outContent, sizeResp, &downloaded) )
                    return (struct responsePOST *) NULL;
                else
                {
                    if(strlen(outContent) != 0)
                    {
                        strcat(data,outContent);

                    }
                }
            }



        }while(sizeResp > 0);
        respuesta->Response =(char *) calloc(strlen(data), sizeof(data));
        strncpy(respuesta->Response,data,strlen(data));
        respuesta->len_response = strlen(data);

        free(data);
    }

    // Cerrar WinHttpCloseHandle(allshit);
    WinHttpCloseHandle(hSession);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hRequest);

    //liberar funciones
    free(WinHttpOpen);
    free(WinHttpCloseHandle);
    free(WinHttpConnect);
    free(WinHttpOpenRequest);
    free(WinHttpSendRequest) ;
    free(WinHttpReceiveResponse);
    free(WinHttpQueryDataAvailable);
    free(WinHttpReadData);
    free(WinHttpQueryHeaders);

    // liberar liberia
    FreeLibrary(LdllHttp);

    return respuesta;
}

int main(void) {
    struct responseGet * rep = Get(
                                 L"C:\\Windows\\System32\\winhttp.dll",
                                 L"pornhub.com",
                                 (WORD) 443,
                                 L"/");
    printf(rep->Response);
    system("pause");
    return 0;
}