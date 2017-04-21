#include <cstdio>
#include <cstring>
#include <windows.h>

#include "reg.h"
#include "types.h"

Reg::Reg() {
    isWow64();
}

void Reg::isWow64() {  
    typedef BOOL(WINAPI *ISWOW64PROCESS)(HANDLE, PBOOL);  
    ISWOW64PROCESS fnIsWow64Process;  
    BOOL bIsWow64 = FALSE;  
    fnIsWow64Process = (ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");  
    if ((fnIsWow64Process) && fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
        KEY_WOW64_64KEY = 0x0100;
    KEY_WOW64_64KEY = 0x0;  
}  

int Reg::open_registry_key(HKEY hKey, char const * regkey_s) {
    puts("open registry key: ");

    HKEY regkey;
    DWORD result;

    result = RegOpenKeyEx(
        hKey,                  // 主鍵
        TEXT(regkey_s),                     // 子鍵
        0,                                  // 選項
        KEY_QUERY_VALUE | KEY_WOW64_64KEY,  // 打開權限
        &regkey                               // 返回打開的句柄
    );            

    if (result == ERROR_SUCCESS) {
        message.success_message("open success");
    }
    else {
        printf("open failed, id: ");
        message.fail_message(message.convert_DWORD_to_Char(result));
        return FALSE;
    }
    RegCloseKey(regkey);
    return TRUE;
}

int Reg::read_registry_value(HKEY hKey, char const * regkey_s, char const * name_s, unsigned char byBuffer[]) {
    puts("read registry value: ");

    HKEY regkey;
    DWORD result;

    result = RegOpenKeyEx(
        hKey,                  // 主鍵
        TEXT(regkey_s),                     // 子鍵
        0,                                  // 選項
        KEY_QUERY_VALUE | KEY_WOW64_64KEY,  // 打開權限
        &regkey                               // 返回打開的句柄
    );            

    if (result == ERROR_SUCCESS) {
        message.success_message("open success");
    }
    else {
        printf("open failed, id: ");
        message.fail_message(message.convert_DWORD_to_Char(result));
        RegCloseKey(regkey);
        return FALSE;
    }

    
    DWORD dwBufSize = 1024;

    result = RegQueryValueEx(
        regkey,                           // hkey
        name_s,                        // lpValueName
        0,                              // lpResverved
        0,                              // lpType
        byBuffer,                       //lpData 
        &dwBufSize                      //lpcbData
    );
    if(result == ERROR_SUCCESS)
    {
        printf("Key value is: ");
        message.success_message((char *)byBuffer);
    }
    else
    {
        printf("Cannot query for key value; Error is: ");
        message.fail_message(message.convert_DWORD_to_Char(result));
        RegCloseKey(regkey);
        return FALSE;
    }
    RegCloseKey(regkey);
    return TRUE;
}

int Reg::create_registry_key(HKEY hKey, char const * regkey_s, char const * lpsubkey_s) {
    puts("create registry key: ");

    HKEY regkey;
    HKEY subKey;
    DWORD result;

    result = RegOpenKeyEx(
        hKey, // 主鍵
        TEXT(regkey_s),   // 子鍵
        0,                  // 選項
        KEY_SET_VALUE | KEY_WOW64_64KEY,    // 打開權限
        &regkey               // 返回打開的句柄
    );            

    if (result == ERROR_SUCCESS) {
        message.success_message("open success");
    }
    else {
        printf("open failed, id: ");
        message.fail_message(message.convert_DWORD_to_Char(result));
        RegCloseKey(regkey);
        return FALSE;
    }

    result = RegCreateKey(regkey, TEXT(lpsubkey_s), &subKey);
    if (result == ERROR_SUCCESS)
    {
        message.success_message("create success");
    }
    else
    {
        printf("create failed, id: ");
        message.fail_message(message.convert_DWORD_to_Char(result));
        RegCloseKey(subKey);
        RegCloseKey(regkey);
        return FALSE;
    }
    RegCloseKey(subKey);
    RegCloseKey(regkey);
    return TRUE;
}

int Reg::create_registry_value(HKEY hKey, char const * regkey_s, char const * lpsubkey_s, char const * name_s, char const * value_s) {
    puts("create registry value: ");

    HKEY regkey;
    HKEY subKey;
    DWORD result;

    result = RegOpenKeyEx(
        hKey, // 主鍵
        TEXT(regkey_s),   // 子鍵
        0,                  // 選項
        KEY_SET_VALUE | KEY_WOW64_64KEY,    // 打開權限
        &regkey               // 返回打開的句柄
    );            

    if (result == ERROR_SUCCESS) {
        message.success_message("open success");
    }
    else {
        printf("open failed, id: ");
        message.fail_message(message.convert_DWORD_to_Char(result));
        RegCloseKey(regkey);
        return FALSE;
    }

    result = RegCreateKey(regkey, TEXT(lpsubkey_s), &subKey);
    if (result == ERROR_SUCCESS)
    {
        message.success_message("create success");
    }
    else
    {
        printf("create failed, id: ");
        message.fail_message(message.convert_DWORD_to_Char(result));
        RegCloseKey(subKey);
        RegCloseKey(regkey);
        return FALSE;
    }
 
    result = RegSetValueEx(
                 subKey,
                 TEXT(name_s),         // Name字段
                 0,              // 保留参数必须填 0
                 REG_SZ,         // 键值类型为字符串
                 (CONST BYTE*)value_s, // 字符串首地址
                 strlen(value_s)   // 字符串长度
             );
 
    if (result == ERROR_SUCCESS)
    {
        message.success_message("set success");
    }
    else
    {
        printf("set failed, id: ");
        message.fail_message(message.convert_DWORD_to_Char(result));
        RegCloseKey(subKey);
        RegCloseKey(regkey);
        return FALSE;
    }
    RegCloseKey(subKey);
    RegCloseKey(regkey);
    return TRUE;
}

int Reg::delete_registry_value(HKEY hKey, char const * regkey_s, char const * name_s) {
    puts("delete registry value: ");

    HKEY regkey;
    DWORD result;

    result = RegOpenKeyEx(
        hKey, // 主鍵
        TEXT(regkey_s),   // 子鍵
        0,                  // 選項
        KEY_SET_VALUE | KEY_WOW64_64KEY,    // 打開權限
        &regkey               // 返回打開的句柄
    );            

    if (result == ERROR_SUCCESS) {
        message.success_message("open success");
    }
    else {
        printf("open failed, id: ");
        message.fail_message(message.convert_DWORD_to_Char(result));
        RegCloseKey(regkey);
        return FALSE;
    }


    result = RegDeleteValue(regkey, name_s);
 
    if (result == ERROR_SUCCESS)
    {
        message.success_message("delete success");
    }
    else
    {
        printf("delete failed, id: ");
        message.fail_message(message.convert_DWORD_to_Char(result));
        RegCloseKey(regkey);
        return FALSE;
    }
    RegCloseKey(regkey);
    return TRUE;
}

int Reg::delete_registry_key(HKEY hKey, char const * regkey_s, char const * subkey_s) {
    puts("delete registry key: ");

    HKEY regkey;
    DWORD result;

    result = RegOpenKeyEx(
        hKey, // 主鍵
        TEXT(regkey_s),   // 子鍵
        0,                  // 選項
        KEY_SET_VALUE | KEY_WOW64_64KEY,    // 打開權限
        &regkey               // 返回打開的句柄
    );            

    if (result == ERROR_SUCCESS) {
        message.success_message("open success");
    }
    else {
        printf("open failed, id: ");
        message.fail_message(message.convert_DWORD_to_Char(result));
        RegCloseKey(regkey);
        return FALSE;
    }


    result = RegDeleteKey(regkey, subkey_s);
 
    if (result == ERROR_SUCCESS)
    {
        message.success_message("delete success");
    }
    else
    {
        printf("delete failed, id: ");
        message.fail_message(message.convert_DWORD_to_Char(result));
        RegCloseKey(regkey);
        return FALSE;
    }
    RegCloseKey(regkey);
    return TRUE;
}

