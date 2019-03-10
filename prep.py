import re
import requests
import parsel
import sys
import os

dummyCppFile = '''#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  

struct solver {
    ll ans;
    void doit(ll t) {
        read();
        solve();
        printf("Case #%lld: %lld\\n", t, ans);
    }

    void read() {
        return;
    }

    void solve() {
        return;
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("A.in","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) { solver ss; ss.doit(i); }
    return 0;
}
'''

tasksJsonFile = '''{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [ "-std=c++14", 
                      "-Wl,--stack=268435456",
                      "-g",
                      "-Wall",
                      "-Wextra",
                      "-pedantic",
                      "-Wformat=2",
                      "-Wfloat-equal",
                      "-Wlogical-op",
                      "-Wredundant-decls",
                      "-Wconversion",
                      "-Wcast-qual",
                      "-Wcast-align",
                      "-Wuseless-cast",
                      "-Wno-shadow",
                      "-Wno-unused-result",
                      "-Wno-unused-parameter",
                      "-Wno-unused-local-typedefs",
                      "-Wno-long-long",
                      "-DLOCAL_PROJECT",
                      "-DLOCAL_DEBUG",
                      "-D_GLIBCXX_DEBUG",
                      "-D_GLIBCXX_DEBUG_PEDANTIC",
                      "${file}" ],
            "group": { "kind": "build", "isDefault": true }
        }
    ]
}
'''

launchJsonFile = '''{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/a.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\\\mingw-w64\\\\mingw64\\\\bin\\\\gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
'''

cCppPropertiesJsonFile = '''{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "C:/mingw-w64/mingw64/bin/g++.exe",
            "intelliSenseMode": "gcc-x64",
            "cStandard": "c11",
            "cppStandard": "c++14"
        }
    ],
    "version": 4
}
'''

def vscodePrep():
    if os.path.isdir(".vscode") : return
    os.mkdir(".vscode")
    with open(".vscode/tasks.json",'w')  as fp : fp.write(tasksJsonFile)
    with open(".vscode/launch.json",'w') as fp : fp.write(launchJsonFile)
    with open(".vscode/c_cpp_properties.json","w") as fp : fp.write(cCppPropertiesJsonFile)

def cppStarter(fn) :
    if os.path.isfile(fn) : return
    with open(fn,"w") as fp : fp.write(dummyCppFile)  

vscodePrep()
cppStarter("A.cpp")
cppStarter("B.cpp")
cppStarter("C.cpp")
cppStarter("D.cpp")