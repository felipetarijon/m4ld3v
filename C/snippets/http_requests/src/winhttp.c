#ifndef UNICODE
    #define UNICODE
    #define _UNICODE
#endif // UNICODE

#include <windows.h>
#include <winhttp.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

struct responseGet
{
    LPCWSTR header;
    LPSTR response;
    DWORD len_header;
    DWORD len_response;
};

struct responsePOST
{
    LPCWSTR header;
    LPSTR response;
    DWORD len_header;
    DWORD len_response;
};

struct responseGet * Get(const wchar_t * host, WORD port, wchar_t * uri);

struct responsePOST * Post(const wchar_t * host, WORD port, wchar_t * uri, char * postData);

struct responseGet * Get(const wchar_t * host, WORD port, wchar_t * uri)
{
    struct responseGet * resp = malloc(sizeof(struct responseGet));

    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;

    hSession = WinHttpOpen(L"FuckAll/6.6(X11;Win$ucks x84_64;rv:66.6)",1,NULL,NULL,0);
    if(hSession == NULL) return (struct responseGet *) NULL;

    hConnect = WinHttpConnect(hSession,host,port,0);
    if(hConnect == NULL) return (struct responseGet *) NULL;

    hRequest = WinHttpOpenRequest(hConnect,L"GET",uri,NULL,NULL,NULL,0);
    if(hRequest == NULL) return (struct responseGet *) NULL;

    BOOL bResult = WinHttpSendRequest(hRequest, NULL,0,NULL,0,0,0);
    if(bResult == FALSE) return (struct responseGet *) NULL;

    bResult = WinHttpReceiveResponse(hRequest,NULL);

    if (bResult) {
        DWORD SizeHeaders = 0;
        WinHttpQueryHeaders(hRequest,22,NULL,NULL,&SizeHeaders,NULL);
        if( GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            resp->header = calloc(SizeHeaders/sizeof(WCHAR),sizeof(WCHAR));
            WinHttpQueryHeaders(hRequest,22,NULL,(LPVOID) resp->header,&SizeHeaders,NULL);
        }

        resp->len_header= (DWORD) SizeHeaders/sizeof(WCHAR);

        DWORD sizeResp, downloaded = 0;
        LPSTR outContent;
        LPSTR data = (char*) calloc(10000000,sizeof(char));
        resp->len_response = 0;

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

        } while(sizeResp > 0);
        resp->response = (char *) calloc(strlen(data), sizeof(data));
        strncpy(resp->response, data, strlen(data));
        resp->len_response = strlen(data);

        free(data);
    }

    WinHttpCloseHandle(hSession);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hRequest);

    return resp;
}

struct responsePOST * Post(const wchar_t * host, WORD port, wchar_t * uri, char * postData)
{
    struct responsePOST * resp = malloc(sizeof(struct responseGet));

    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;

    hSession = WinHttpOpen(L"FuckAll/6.6(X11;Win$ucks x84_64;rv:66.6)",1,NULL,NULL,0);
    if (hSession == NULL) return (struct responsePOST *) NULL;

    hConnect = WinHttpConnect(hSession, host, port, 0);
    if (hConnect == NULL) return (struct responsePOST *) NULL;

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

    if (bResult)
    {
        DWORD SizeHeaders = 0;
        WinHttpQueryHeaders(hRequest,22,NULL,NULL,&SizeHeaders,NULL);
        if( GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            resp->header = calloc(SizeHeaders/sizeof(WCHAR),sizeof(WCHAR));
            WinHttpQueryHeaders(hRequest,22,NULL,(LPVOID) resp->header,&SizeHeaders,NULL);
        }

        resp->len_header= (DWORD) SizeHeaders/sizeof(WCHAR);

        DWORD sizeResp, downloaded = 0;
        LPSTR outContent;
        LPSTR data = (char*) calloc(10000000,sizeof(char));
        resp->len_response = 0;

        do {
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
        } while (sizeResp > 0);
        resp->response = (char *) calloc(strlen(data), sizeof(data));
        strncpy(resp->response, data, strlen(data));
        resp->len_response = strlen(data);

        free(data);
    }

    WinHttpCloseHandle(hSession);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hRequest);

    return resp;
}

int main() {
    struct responseGet * resp = Get(
                                 L"eogtmsvtjz6apes.m.pipedream.net",
                                 (WORD) 80,
                                 L"/");
    printf(resp->response);
    printf("\n\n");

    struct responsePOST * resp2 = Post(
                                 L"eogtmsvtjz6apes.m.pipedream.net",
                                 (WORD) 80,
                                 L"/",
                                 "EAE CARAIOOO");
    printf(resp2->response);
    printf("\n");

    system("pause");

    return EXIT_SUCCESS;
}
