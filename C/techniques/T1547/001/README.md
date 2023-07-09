# Auto Start Execution

Implements two different ways of achieving basic persistence according to MITRE ATT&CK [T1547/001](https://attack.mitre.org/techniques/T1547/001/):
- **Startup Folder:** copies itself to startup folder (%appdata%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\newname.exe).
- **Registry Keys:** set itself into Windows startup by using Registry Keys Run or RunOnce within HKCU.

## Build

Each .c file has a different approach.

```bash
gcc -o startup_folder src/startup_folder.c
gcc -o reg_keys src/reg_keys.c
```

## Run

```
./startup_folder
./reg_keys
```