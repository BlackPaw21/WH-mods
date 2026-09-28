// ==WindhawkMod==
// @id              net-toggle
// @name            Net-Toggle
// @description     Toggle physical adapters and monitor DNS status from the system tray
// @version         2.2.0
// @author          BlackPaw
// @github          https://github.com/BlackPaw21
// @donateUrl       https://ko-fi.com/blackpaw21
// @license         MIT
// @include         windhawk.exe
// @compilerOptions -lshell32 -lgdi32 -luser32 -lole32 -luuid -liphlpapi -lws2_32 -ladvapi32 -lsetupapi -lcfgmgr32 -DWIN32_LEAN_AND_MEAN -ffp-exception-behavior=maytrap
// ==/WindhawkMod==

// ==WindhawkModSettings==
/*
- dnsServer: "8.8.8.8"
  $name: Primary DNS server
  $description: IPv4 address of the DNS server to monitor (leave blank to disable DNS monitoring)

- dnsProbe: udp
  $name: Primary DNS check method
  $description: >-
    Real DNS query is the most accurate. The TCP options only verify that the
    port accepts connections — pick 853/443 for DoT/DoH endpoints like NextDNS.
  $options:
  - udp: Real DNS query (UDP 53)
  - tcp: TCP connect (port 53)
  - dot: DNS-over-TLS endpoint (TCP 853)
  - doh: DNS-over-HTTPS endpoint (TCP 443)

- dnsServer2: ""
  $name: Secondary DNS server
  $description: Optional fallback DNS server, monitored alongside the primary

- dnsProbe2: udp
  $name: Secondary DNS check method
  $options:
  - udp: Real DNS query (UDP 53)
  - tcp: TCP connect (port 53)
  - dot: DNS-over-TLS endpoint (TCP 853)
  - doh: DNS-over-HTTPS endpoint (TCP 443)
  $description: Check method for the secondary DNS server

- pingInterval: 10
  $name: Check interval (seconds)
  $description: How often to check DNS reachability (minimum 5)
*/
// ==/WindhawkModSettings==

// ==WindhawkModReadme==
/*
# Net-Toggle

Quickly turn your network on or off with a double-click right from your system tray. Net-Toggle lets you easily manage your network hardware, toggle Wi-Fi, and monitor your connection health and ping at a glance.

![Net-Toggle Context Menu](https://i.imgur.com/DWezrMb.png)

Hover over the tray icon at any time to see live connection details:
- **DNS:** Confirms if domain name lookup is working properly.
- **ICMP:** Your ping — measures response latency (in milliseconds) and packet loss to show connection speed and stability.

## Colors Legend (Tray Icon)

**🔴 Red** — Network is OFF

![Red](https://i.imgur.com/1jOe8EE.png)

**🟡 Yellow** — Network toggle or reset is in progress

![Yellow](https://i.imgur.com/rvXLTas.png)

**🟢 Green** — Network is ON, connection is healthy

![Green](https://i.imgur.com/l3UjhAQ.png)

**🟠 Orange** — Network is ON, primary DNS is down — the secondary (fallback) DNS is still answering

![Orange](https://i.imgur.com/3H49bgH.png)

**⚪ Grey** — Network is ON, DNS is unreachable

![Grey](https://i.imgur.com/EWrbzpv.png)

**🔵 Blue** — Network is ON, no DNS server configured

![Blue](https://i.imgur.com/sOQK6Cp.png)

## How to Use It

1. **Find the Icon:** Look in your system tray (bottom-right corner, next to the clock) for the network icon. If it is hidden, click the `^` arrow.
2. **Double-click to Toggle:** Double-click the icon to toggle your physical network adapters on or off (double-click prevents accidental disconnects).
3. **Middle-click to Reset:** Quickly resets your network connection by cycling adapters and flushing the DNS cache.
4. **Right-click for Menu:** Manage individual adapters, toggle Wi-Fi adapters, open Windows Network Settings, or open Windhawk.
5. **Approve the Windows Prompt:** When toggling or resetting, Windows will show a UAC prompt asking for permission. Click **Yes** (Windows requires administrator permission to change hardware states).
6. **(Optional) Configure DNS Monitoring:** In Windhawk mod settings, enter your preferred DNS server (like `8.8.8.8` or `1.1.1.1`) and optionally a backup server (like `8.8.4.4`).
   - **Real DNS Query** *(Default)* — Recommended for almost everyone; accurately tests real domain resolution.
   - **TCP / DoT / DoH** — Use if your network filters standard UDP queries and you monitor custom endpoints.

## Changelog

# 2.2.0
- **New:** Submenu listing physical adapters by unique GUID to individually toggle adapters on or off.
- **New:** Direct Wi-Fi adapter toggle in the right-click menu ("Disable Wifi Adapters" / "Enable Wifi Adapters").
- **New:** DNS monitoring tooltip now displays live ICMP round-trip time (RTT) and sample loss statistics.
- **Improved:** Tray icon toggle now triggers on double-click instead of single click to prevent accidental network disconnections.
- **Improved:** Adapter inventory filters out virtual adapters and hidden miniports to show only physical hardware.
- **Improved:** Adapters submenu dynamically refreshes adapter states whenever the submenu opens.
- **Improved:** Reduced click cooldown from 10s to 2s for a significantly more responsive tray experience.
- **Fixed:** Eliminated DHCP race condition where the tray icon prematurely showed offline immediately after re-enabling adapters.
- **Fixed:** Network toggling now reliably restores connectivity without requiring a full reset or middle-click.
- **Fixed:** Corrected network notification handle cancellation and hardened elevated command verification.
- **Fixed:** Replaced unbounded thread wait during uninitialization with a bounded wait for clean shutdown.

# 2.1.1
- **Fixed:** Mod no longer crashes on reload.
- **Fixed:** Unstable state on rapid clicks resolved.
- **Added:** Description for the secondary DNS server check method setting.

# 2.1.0
- **New:** Secondary DNS server — monitor a primary and fallback pair (Google, Cloudflare, NextDNS all publish two IPs). New orange icon state when only the fallback is answering.
- **New:** Per-server check method — real DNS query (default), TCP 53, or DNS-over-TLS / DNS-over-HTTPS endpoint reachability for providers like NextDNS.
- **Improved:** Default check now sends a real DNS query instead of a bare TCP connect — fixes false "DNS unreachable" results on networks that filter TCP port 53.
- **Improved:** Tray tooltip shows per-server ✓ / ✗ status.
- **Improved:** Icon shows green ("checking") immediately after the network comes back up instead of flashing grey until the first check completes.
- **Fixed:** Rare timing issue that could briefly show outdated DNS status after changing settings.
- **Fixed:** Possible freeze when disabling the mod or restarting Explorer while a network toggle was in progress.

# 2.0.0
- **New:** Complete rebuild with DNS monitoring, WiFi-style tray icon, and network reset.
- **New:** DNS monitoring — the icon monitors your connection and changes color if your internet drops out (configurable in Mod Settings).
- **New:** WiFi-style tray icon with 5 color states (Red, Yellow, Blue, Green, Grey).
- **New:** Middle-click → full network reset — disables all adapters, flushes DNS, re-enables them.
- **New:** Right-click context menu — toggle network, open Network Settings, open Windhawk.
- **New:** Donate button on the mod page.
- **Improved:** Tray icon is now independent from the Windhawk app and no longer groups with it in the taskbar.
- **Improved:** Tray icon persists reliably across Explorer restarts.
- **Improved:** Icon stays in sync even if you disable your adapter directly in Windows Settings.

# 1.0.0
- Initial release.
*/
// ==/WindhawkModReadme==

// iphlpapi.h only declares the netioapi APIs
// (GetIfTable2 / MIB_IF_TABLE2 / FreeMibTable) when the winsock2 types are
// already in scope. -DWIN32_LEAN_AND_MEAN in compiler options prevents windows.h
// from including the legacy winsock.h.
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windhawk_utils.h>
#include <windows.h>
#include <shellapi.h>
#include <shobjidl.h>
#include <propkey.h>
#include <propidl.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <setupapi.h>
#include <devguid.h>
#include <cfgmgr32.h>
#include <netioapi.h>
#include <vector>
#include <new>
#include <strsafe.h>
#include <math.h>

#define TRAY_ICON_ID 1
#define WM_TRAY_CALLBACK (WM_USER + 1)
#define WM_UPDATE_TRAY_STATE (WM_USER + 2)
#define WM_SETTINGS_CHANGED (WM_USER + 4)
#define WM_TRIGGER_PING (WM_USER + 5)
#define DNS_PING_TIMER_ID 2
#define DNS_RECOVERY_TIMER_ID 3

#define MENU_TOGGLE_NET    1
#define MENU_TOGGLE_WIFI   3
#define MENU_ADAPTER_FIRST 100
#define MENU_NET_SETTINGS  2
#define MENU_OPEN_WINDHAWK 9000

// Stable GUID that gives our tray icon a process-independent identity.
static const GUID NETTOGGLE_TRAY_GUID =
    {0x246764CF, 0xF857, 0x4399, {0x8D, 0x3D, 0x22, 0x76, 0x1A, 0x6A, 0xBD, 0x95}};

const DWORD CLICK_DEBOUNCE_MS = 2000;
static volatile DWORD g_enableGracePeriodUntilTick = 0;

static const DWORD NETWATCH_POLL_INTERVAL = 15000;  // 15s per fallback poll tick
static const DWORD NETWATCH_POLL_RETRIES  = 4;      // 4 × 15s = 60s then retry NotifyAddrChange
static const int   MIN_PING_INTERVAL_SEC  = 5;
static const int   DNS_PROBE_TIMEOUT_SEC  = 2;       // TCP connect deadline…
static const int   DNS_PROBE_TIMEOUT_USEC = 500000;  // …2.5s total
static const int   DNS_UDP_ATTEMPTS       = 2;       // query + 1 retransmit
static const int   DNS_UDP_WAIT_SEC       = 1;       // per-attempt reply wait…
static const int   DNS_UDP_WAIT_USEC      = 250000;  // …1.25s each, 2.5s worst case

static LONG g_isProcessingClick = 0;
static LONG g_trayIconInstalled = 0;
static LONG g_networkIsUp = 1;
static volatile LONG g_networkStateKnown = 0;
static HANDLE g_trayThread = nullptr;
static volatile HWND g_trayHwnd = nullptr;
static HINSTANCE g_hInstance = nullptr;
static volatile DWORD g_lastClickTime = 0;
static UINT g_taskbarCreatedMsg = 0;
static HANDLE g_activeWorkerThread = nullptr;

// DNS monitoring — two probe slots: [0] = primary, [1] = secondary.
static volatile LONG g_dnsIp[2]    = {0, 0};    // IPv4, network byte order; 0 = unconfigured
static volatile LONG g_dnsProbe[2] = {0, 0};    // DnsProbeMethod per slot
static volatile LONG g_dnsUp[2]    = {-1, -1};  // -1 = not checked yet, 0 = down, 1 = up
static volatile LONG g_dnsGeneration = 0;
static volatile LONG g_networkGeneration = 0;
static volatile LONG g_lastNotifiedNetworkState = -1;
struct IcmpResult { DWORD ip; LONG generation; int slot; int status; DWORD rtt; };
struct IcmpHistory {
    DWORD ip = 0;
    BYTE samples[10] = {};
    int count = 0;
    int next = 0;
    int status = -1;  // unknown, completed failure, success
    DWORD rtt = 0;
};
static IcmpHistory g_icmpHistory[2];
static SRWLOCK g_icmpLock = SRWLOCK_INIT;
static DWORD g_pingIntervalMs = 10000;
static volatile LONG g_dnsWorkerRunning = 0;
static HANDLE g_dnsWorkerThread = nullptr;

// Network watch thread
static HANDLE g_netWatchThread = nullptr;
static HANDLE g_shutdownEvent = nullptr;

// Current tray icon handle (destroy before replace)
static HICON g_currentIcon = nullptr;

static WCHAR   g_windhawkPath[MAX_PATH]  = {};
static WCHAR   g_ddoresDllPath[MAX_PATH] = {};
static HICON   g_hWindHawkIcon = nullptr;
static HBITMAP g_hWindHawkBmp  = nullptr;

// helpers

void LogLastError(LPCWSTR context) {
    DWORD error = GetLastError();
    if (error == 0) return;

    LPWSTR errorMsg = nullptr;
    if (FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       (LPWSTR)&errorMsg, 0, nullptr)) {
        Wh_Log(L"[ERROR] %s: %s (0x%X)", context, errorMsg, error);
        LocalFree(errorMsg);
    } else {
        Wh_Log(L"[ERROR] %s: Error %d", context, error);
    }
}

struct AdapterInfo {
    GUID id = {};
    WCHAR name[128] = {};
    int admin = -1; // -1 unknown, 0 disabled, 1 enabled
    bool physical = false;
    bool isWifi = false;
};

static bool ContainsCaseInsensitive(const WCHAR* haystack, const WCHAR* needle) {
    if (!haystack || !needle) return false;
    size_t needleLen = wcslen(needle);
    size_t haystackLen = wcslen(haystack);
    if (needleLen > haystackLen) return false;
    for (size_t i = 0; i <= haystackLen - needleLen; ++i) {
        if (_wcsnicmp(&haystack[i], needle, needleLen) == 0) return true;
    }
    return false;
}

static bool EnumerateAdapters(std::vector<AdapterInfo>& adapters) {
    HDEVINFO devices = SetupDiGetClassDevsW(&GUID_DEVCLASS_NET, nullptr, nullptr, DIGCF_PRESENT);
    if (devices == INVALID_HANDLE_VALUE) return false;
    for (DWORD index = 0;; ++index) {
        SP_DEVINFO_DATA device = {sizeof(device)};
        if (!SetupDiEnumDeviceInfo(devices, index, &device)) break;
        HKEY key = SetupDiOpenDevRegKey(devices, &device, DICS_FLAG_GLOBAL, 0, DIREG_DRV, KEY_READ);
        if (key == INVALID_HANDLE_VALUE) continue;
        WCHAR idText[64] = {};
        DWORD bytes = sizeof(idText), type = 0;
        LONG status = RegQueryValueExW(key, L"NetCfgInstanceId", nullptr, &type,
                                       reinterpret_cast<BYTE*>(idText), &bytes);
        if (status != ERROR_SUCCESS || type != REG_SZ || bytes > sizeof(idText)) {
            RegCloseKey(key);
            continue;
        }

        DWORD characteristics = 0;
        DWORD charBytes = sizeof(characteristics);
        DWORD charType = 0;
        bool hasChar = (RegQueryValueExW(key, L"Characteristics", nullptr, &charType,
                                         reinterpret_cast<BYTE*>(&characteristics), &charBytes) == ERROR_SUCCESS && charType == REG_DWORD);
        RegCloseKey(key);

        idText[ARRAYSIZE(idText) - 1] = L'\0';
        AdapterInfo adapter;
        if (FAILED(CLSIDFromString(idText, &adapter.id))) continue;
        DWORD propertyType = 0;
        if (!SetupDiGetDeviceRegistryPropertyW(devices, &device, SPDRP_FRIENDLYNAME,
                &propertyType, reinterpret_cast<BYTE*>(adapter.name), sizeof(adapter.name), nullptr))
            SetupDiGetDeviceRegistryPropertyW(devices, &device, SPDRP_DEVICEDESC,
                &propertyType, reinterpret_cast<BYTE*>(adapter.name), sizeof(adapter.name), nullptr);
        adapter.name[ARRAYSIZE(adapter.name) - 1] = L'\0';

        if (hasChar) {
            adapter.physical = (characteristics & 0x04) != 0; // NCF_PHYSICAL
        }

        if (ContainsCaseInsensitive(adapter.name, L"Wi-Fi") ||
            ContainsCaseInsensitive(adapter.name, L"WiFi") ||
            ContainsCaseInsensitive(adapter.name, L"Wireless") ||
            ContainsCaseInsensitive(adapter.name, L"802.11") ||
            ContainsCaseInsensitive(adapter.name, L"WLAN")) {
            adapter.isWifi = true;
        }

        MIB_IF_ROW2 row = {};
        row.InterfaceGuid = adapter.id;
        if (GetIfEntry2(&row) == NO_ERROR) {
            adapter.admin = row.AdminStatus == NET_IF_ADMIN_STATUS_UP ? 1 : 0;
            if (!hasChar) {
                adapter.physical = row.InterfaceAndOperStatusFlags.HardwareInterface != FALSE;
            }
            if (row.Type == IF_TYPE_IEEE80211 || row.MediaType == NdisMediumNative802_11) {
                adapter.isWifi = true;
            }
        } else {
            ULONG flags = 0, problem = 0;
            if (CM_Get_DevNode_Status(&flags, &problem, device.DevInst, 0) == CR_SUCCESS) {
                if (problem == CM_PROB_DISABLED) adapter.admin = 0;
                else if (flags & DN_STARTED) adapter.admin = 1;
            }
        }
        adapters.push_back(adapter);
    }
    SetupDiDestroyDeviceInfoList(devices);
    return true;
}

BOOL CheckActualNetworkState() {
    std::vector<AdapterInfo> adapters;
    if (!EnumerateAdapters(adapters)) {
        if (InterlockedExchange(&g_networkStateKnown, 0) != 0) InterlockedIncrement(&g_networkGeneration);
        Wh_Log(L"Network adapter inventory unavailable");
        return InterlockedOr(&g_networkIsUp, 0) == 1;
    }
    bool anyRelevant = false, anyEnabled = false, unresolved = false;
    for (const auto& adapter : adapters) {
        if (!adapter.physical) continue;
        anyRelevant = true;
        if (adapter.admin == 1) anyEnabled = true;
        if (adapter.admin < 0) unresolved = true;
    }
    if (!anyRelevant || (unresolved && !anyEnabled)) {
        if (InterlockedExchange(&g_networkStateKnown, 0) != 0) InterlockedIncrement(&g_networkGeneration);
        return InterlockedOr(&g_networkIsUp, 0) == 1;
    }
    if (InterlockedExchange(&g_networkStateKnown, 1) != 1) InterlockedIncrement(&g_networkGeneration);
    return anyEnabled;
}

BOOL RunPowerShellCommand(LPCWSTR psCommand) {
    Wh_Log(L"Executing PowerShell command");

    WCHAR cmdArgs[2048];
    if (FAILED(StringCchPrintfW(cmdArgs, ARRAYSIZE(cmdArgs),
        L"-NoProfile -NonInteractive -WindowStyle Hidden -Command \"$ErrorActionPreference='Stop'; %s\"", psCommand))) {
        Wh_Log(L"Failed to format command");
        return FALSE;
    }

    SHELLEXECUTEINFOW sei = {sizeof(sei)};
    sei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NO_CONSOLE;
    sei.hwnd = nullptr;
    sei.lpVerb = L"runas";
    WCHAR powershellPath[MAX_PATH];
    if (!GetSystemDirectoryW(powershellPath, ARRAYSIZE(powershellPath)) ||
        FAILED(StringCchCatW(powershellPath, ARRAYSIZE(powershellPath),
                             L"\\WindowsPowerShell\\v1.0\\powershell.exe"))) return FALSE;
    sei.lpFile = powershellPath;
    sei.lpParameters = cmdArgs;
    sei.nShow = SW_HIDE;

    if (!ShellExecuteExW(&sei)) {
        DWORD error = GetLastError();
        if (error == ERROR_CANCELLED) {
            Wh_Log(L"UAC prompt cancelled by user");
        } else {
            Wh_Log(L"ShellExecuteEx failed: %d", error);
        }
        return FALSE;
    }

    Wh_Log(L"UAC cleared. Waiting for PowerShell to complete...");

    if (!sei.hProcess) {
        Wh_Log(L"No process handle returned");
        return FALSE;
    }

    DWORD waitResult;
    bool overdue = false;
    do {
        waitResult = WaitForSingleObject(sei.hProcess, 5000);
        if (waitResult == WAIT_TIMEOUT && !overdue) {
            Wh_Log(L"PowerShell still running; keeping adapter operation busy");
            overdue = true;
        }
        if (waitResult == WAIT_TIMEOUT && g_shutdownEvent &&
            WaitForSingleObject(g_shutdownEvent, 0) == WAIT_OBJECT_0) {
            CloseHandle(sei.hProcess);
            return FALSE;
        }
    } while (waitResult == WAIT_TIMEOUT);
    if (waitResult != WAIT_OBJECT_0) {
        CloseHandle(sei.hProcess);
        return FALSE;
    }

    DWORD exitCode = 1;
    if (!GetExitCodeProcess(sei.hProcess, &exitCode)) {
        LogLastError(L"GetExitCodeProcess");
        CloseHandle(sei.hProcess);
        return FALSE;
    }

    CloseHandle(sei.hProcess);
    Wh_Log(L"Process exited with code: %d", exitCode);
    if (exitCode == 0) {
        return TRUE;
    } else {
        Wh_Log(L"PowerShell command failed (exit %d) — network state unchanged", exitCode);
        return FALSE;
    }
}

// ==============================================================================
// Feature B — DNS Reachability Probes
// ==============================================================================

enum DnsProbeMethod : LONG {
    PROBE_UDP_DNS = 0,  // real DNS query over UDP 53 (default)
    PROBE_TCP_53  = 1,  // bare TCP connect to port 53
    PROBE_TCP_853 = 2,  // DNS-over-TLS endpoint reachability
    PROBE_TCP_443 = 3,  // DNS-over-HTTPS endpoint reachability
};

// Overall DNS health derived from the per-slot results.
enum DnsOverall {
    DNS_NONE,      // no server configured — monitoring disabled
    DNS_CHECKING,  // configured but no probe has completed yet
    DNS_OK,        // effective primary is answering
    DNS_DEGRADED,  // primary down, fallback answering
    DNS_DOWN,      // every configured server failed its probe
};

// TCP handshake to the given port. Success only when the connect completes —
// for DoT (853) / DoH (443) endpoints and explicit TCP:53 checks, a refused
// connection means the service is down. ICMP is measured separately.
static BOOL ProbeTcpConnect(DWORD ipAddr, WORD port) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        Wh_Log(L"ProbeTcpConnect: socket() failed (%d)", WSAGetLastError());
        return FALSE;
    }

    u_long nonBlocking = 1;
    ioctlsocket(sock, FIONBIO, &nonBlocking);

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ipAddr;  // network byte order from InetPtonW
    addr.sin_port = htons(port);

    int connectResult = connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    int connectErr = (connectResult == SOCKET_ERROR) ? WSAGetLastError() : 0;

    BOOL reachable = FALSE;
    if (connectResult == 0) {
        reachable = TRUE;
    } else if (connectErr == WSAEWOULDBLOCK || connectErr == WSAEINPROGRESS) {
        fd_set writeSet, exceptSet;
        FD_ZERO(&writeSet);
        FD_ZERO(&exceptSet);
        FD_SET(sock, &writeSet);
        FD_SET(sock, &exceptSet);
        TIMEVAL tv = {DNS_PROBE_TIMEOUT_SEC, DNS_PROBE_TIMEOUT_USEC};
        int sel = select(0, nullptr, &writeSet, &exceptSet, &tv);
        if (sel > 0 && FD_ISSET(sock, &writeSet)) {
            int sockErr = 0;
            int optLen = sizeof(sockErr);
            getsockopt(sock, SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&sockErr), &optLen);
            reachable = (sockErr == 0);
        } else {
            Wh_Log(L"ProbeTcpConnect: TCP:%u timed out or select error (%d)", port, WSAGetLastError());
        }
    } else {
        Wh_Log(L"ProbeTcpConnect: connect() failed immediately (%d)", connectErr);
    }

    closesocket(sock);
    return reachable;
}

// Sends a real DNS query (NS for the root zone) and waits for any reply with a
// matching transaction ID. Any response — even REFUSED — proves a resolver is
// alive at that address. This is more accurate than a TCP probe: many networks
// filter TCP:53 while UDP DNS works fine, which previously caused false
// "DNS unreachable" reports. One retransmit guards against packet loss.
static BOOL ProbeDnsUdp(DWORD ipAddr) {
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        Wh_Log(L"ProbeDnsUdp: socket() failed (%d)", WSAGetLastError());
        return FALSE;
    }

    u_long nonBlocking = 1;
    ioctlsocket(sock, FIONBIO, &nonBlocking);

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ipAddr;  // network byte order from InetPtonW
    addr.sin_port = htons(53);

    // Connected UDP: the stack filters replies by peer address and surfaces
    // ICMP port-unreachable as a recv error instead of silence.
    if (connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
        Wh_Log(L"ProbeDnsUdp: connect() failed (%d)", WSAGetLastError());
        closesocket(sock);
        return FALSE;
    }

    WORD txnId = (WORD)(GetTickCount() ^ (GetCurrentThreadId() << 1));
    if (txnId == 0) txnId = 0x4E54;  // any nonzero value

    // 12-byte header (RD set, QDCOUNT=1) + root QNAME + QTYPE=NS + QCLASS=IN.
    BYTE query[17] = {
        (BYTE)(txnId >> 8), (BYTE)(txnId & 0xFF),
        0x01, 0x00,                          // flags: recursion desired
        0x00, 0x01,                          // QDCOUNT = 1
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // ANCOUNT / NSCOUNT / ARCOUNT
        0x00,                                // QNAME = root
        0x00, 0x02,                          // QTYPE = NS
        0x00, 0x01,                          // QCLASS = IN
    };

    BOOL reachable = FALSE;
    for (int attempt = 0; attempt < DNS_UDP_ATTEMPTS && !reachable; attempt++) {
        if (send(sock, reinterpret_cast<const char*>(query), sizeof(query), 0) == SOCKET_ERROR) {
            Wh_Log(L"ProbeDnsUdp: send() failed (%d)", WSAGetLastError());
            break;
        }

        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(sock, &readSet);
        TIMEVAL tv = {DNS_UDP_WAIT_SEC, DNS_UDP_WAIT_USEC};
        int sel = select(0, &readSet, nullptr, nullptr, &tv);
        if (sel <= 0 || !FD_ISSET(sock, &readSet)) continue;  // no reply yet — retransmit

        BYTE resp[512];
        int len = recv(sock, reinterpret_cast<char*>(resp), sizeof(resp), 0);
        if (len == SOCKET_ERROR) {
            if (WSAGetLastError() == WSAEMSGSIZE) {
                // A larger-than-buffer datagram still arrived from the server.
                len = sizeof(resp);
            } else {
                // e.g. WSAECONNRESET = ICMP port unreachable — try again.
                continue;
            }
        }
        // Valid reply: full header, matching transaction ID, QR bit set.
        if (len >= 12 &&
            resp[0] == (BYTE)(txnId >> 8) && resp[1] == (BYTE)(txnId & 0xFF) &&
            (resp[2] & 0x80)) {
            reachable = TRUE;
        }
    }

    closesocket(sock);
    return reachable;
}

// Routes a probe to the method configured for the slot.
static BOOL ProbeDnsServer(DWORD ipAddr, LONG method) {
    switch (method) {
        case PROBE_TCP_53:  return ProbeTcpConnect(ipAddr, 53);
        case PROBE_TCP_853: return ProbeTcpConnect(ipAddr, 853);
        case PROBE_TCP_443: return ProbeTcpConnect(ipAddr, 443);
        case PROBE_UDP_DNS:
        default:            return ProbeDnsUdp(ipAddr);
    }
}

static BOOL AnyDnsConfigured() {
    return InterlockedOr(&g_dnsIp[0], 0) != 0 || InterlockedOr(&g_dnsIp[1], 0) != 0;
}

static DnsOverall GetDnsOverall() {
    int configured = 0;
    int firstUp = -1;  // position (0-based, configured-only) of the first answering server
    bool anyUnknown = false;
    for (int i = 0; i < 2; i++) {
        if (InterlockedOr(&g_dnsIp[i], 0) == 0) continue;
        LONG up = InterlockedOr(&g_dnsUp[i], 0);
        int pos = configured++;
        if (up == 1 && firstUp < 0) firstUp = pos;
        if (up == -1) anyUnknown = true;
    }
    if (configured == 0) return DNS_NONE;
    if (firstUp == 0) return DNS_OK;       // effective primary answering
    if (firstUp > 0) return DNS_DEGRADED;  // only the fallback is answering
    return anyUnknown ? DNS_CHECKING : DNS_DOWN;
}

// ==============================================================================
// Feature C — Wifi-Shape Icon
// ==============================================================================

// Draws a wifi fan (3 arc bands + center dot) into a 32-bit pre-multiplied-alpha
// DIB.  We work at 2× resolution then down-sample 2×2 → 1 for cheap anti-aliasing.
//
// Arc geometry: the fan is centred at the bottom-centre of the icon, spanning
// ±65° either side of straight-up (i.e. the sweep covers 130° of arc).
// Three rings at outer/mid/inner radii with a proportional pen width, plus a
// small filled dot at the origin.

static void DrawWifiIcon(DWORD* px, int W, int H, BYTE r, BYTE g, BYTE b) {
    // Arc parameters (in icon-pixel units)
    float cx = W * 0.5f;
    float cy = H * 0.88f - 3.0f;   // origin sits near the bottom

    float outerR = W * 0.598f;
    float midR   = W * 0.403f;
    float innerR = W * 0.221f;
    float dotR   = W * 0.098f;
    float penW   = W * 0.143f;  // arc stroke width

    // Arc spans ±65° from straight-up (270° in standard coords)
    const float PI = 3.14159265f;
    float halfSweep = 65.0f * PI / 180.0f;
    float baseAngle = 270.0f * PI / 180.0f;    // pointing up
    float a0 = baseAngle - halfSweep;
    float a1 = baseAngle + halfSweep;

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            float dx = x + 0.5f - cx;
            float dy = y + 0.5f - cy;
            float dist = sqrtf(dx * dx + dy * dy);

            // Determine if pixel centre is on one of the three arc bands
            bool onArc = false;
            if (dist > dotR) {
                float radii[3] = { outerR, midR, innerR };
                for (int i = 0; i < 3; i++) {
                    if (fabsf(dist - radii[i]) <= penW * 0.5f) {
                        // Check angular range
                        float angle = atan2f(dy, dx);
                        // Normalise to [0, 2π)
                        if (angle < 0) angle += 2.0f * PI;
                        float a0n = a0, a1n = a1;
                        if (a0n < 0) a0n += 2.0f * PI;
                        if (a1n < 0) a1n += 2.0f * PI;
                        bool inSweep = (a0n <= a1n)
                            ? (angle >= a0n && angle <= a1n)
                            : (angle >= a0n || angle <= a1n);
                        if (inSweep) { onArc = true; break; }
                    }
                }
            }

            // Determine if pixel is in the centre dot
            bool onDot = (dist <= dotR);

            if (onArc || onDot) {
                // Simple coverage fraction for the outermost ring edge (cheap AA)
                float alpha = 1.0f;
                if (onArc) {
                    // Edge softening: ramp alpha over 1px at outer boundary
                    float nearestR = 0;
                    float radii[3] = { outerR, midR, innerR };
                    float minDelta = 1e9f;
                    for (int i = 0; i < 3; i++) {
                        float d = fabsf(dist - radii[i]);
                        if (d < minDelta) { minDelta = d; nearestR = radii[i]; }
                    }
                    float edge = fabsf(dist - nearestR) - (penW * 0.5f - 1.0f);
                    if (edge > 0) alpha = 1.0f - edge;
                    if (alpha < 0) alpha = 0;
                }
                DWORD a8 = (DWORD)(alpha * 255.0f + 0.5f);
                if (a8 > 255) a8 = 255;
                DWORD pr = (r * a8 + 127) / 255;
                DWORD pg = (g * a8 + 127) / 255;
                DWORD pb = (b * a8 + 127) / 255;
                px[y * W + x] = (a8 << 24) | (pr << 16) | (pg << 8) | pb;
            }
        }
    }
}

HICON CreateColoredDotIcon(BOOL netUp, DnsOverall dns, BOOL pending) {
    int cx = GetSystemMetrics(SM_CXSMICON);
    int cy = GetSystemMetrics(SM_CYSMICON);

    COLORREF iconColor;
    if (pending)                   iconColor = RGB(240, 180, 0);   // Yellow — toggle/reset in progress
    else if (!netUp)               iconColor = RGB(220, 50,  50);  // Red — network off
    else if (dns == DNS_NONE)      iconColor = RGB(70,  130, 255); // Blue — no DNS configured
    else if (dns == DNS_OK ||
             dns == DNS_CHECKING)  iconColor = RGB(60,  220, 60);  // Green — healthy (or first check pending)
    else if (dns == DNS_DEGRADED)  iconColor = RGB(255, 120, 0);   // Orange — only the fallback DNS answers
    else                           iconColor = RGB(160, 160, 160); // Grey — DNS unreachable

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = cx;
    bmi.bmiHeader.biHeight      = -cy;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    HDC hdcScreen = GetDC(nullptr);
    void* bits = nullptr;
    HBITMAP hBmp = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, hdcScreen);
    if (!hBmp) return nullptr;

    if (bits) {
        DWORD* pixels = (DWORD*)bits;
        memset(pixels, 0, (size_t)cx * cy * 4);
        DrawWifiIcon(pixels, cx, cy,
                     GetRValue(iconColor), GetGValue(iconColor), GetBValue(iconColor));
    }

    HBITMAP hMask = CreateBitmap(cx, cy, 1, 1, nullptr);
    if (hMask) {
        HDC hdcMask = CreateCompatibleDC(nullptr);
        HGDIOBJ hOld = SelectObject(hdcMask, hMask);
        PatBlt(hdcMask, 0, 0, cx, cy, WHITENESS);
        SelectObject(hdcMask, hOld);
        DeleteDC(hdcMask);
    }

    ICONINFO ii = {};
    ii.fIcon    = TRUE;
    ii.hbmColor = hBmp;
    ii.hbmMask  = hMask ? hMask : hBmp;
    HICON hResult = CreateIconIndirect(&ii);

    DeleteObject(hBmp);
    if (hMask) DeleteObject(hMask);

    return hResult;
}

// ==============================================================================
// Tray Icon
// ==============================================================================

// Appends a "\nDNS1 8.8.8.8 ✓" status line to the tooltip (bounds-checked).
static void AppendDnsTipLine(WCHAR* tip, size_t cap, int slot, LPCWSTR label) {
    LONG ip = InterlockedOr(&g_dnsIp[slot], 0);
    if (ip == 0) return;
    LONG up = InterlockedOr(&g_dnsUp[slot], 0);

    IN_ADDR ia = {};
    ia.s_addr = (ULONG)ip;
    WCHAR ipStr[16] = L"?";
    InetNtopW(AF_INET, &ia, ipStr, ARRAYSIZE(ipStr));

    LPCWSTR mark = (up == 1) ? L"✓" : (up == 0) ? L"✗" : L"…";
    size_t len = wcslen(tip);
    if (len + 24 >= cap) return;  // "\nDNS2 255.255.255.255 ✗" worst case
    swprintf_s(tip + len, cap - len, L"\n%s %s %s", label, ipStr, mark);
}

static void AppendIcmpTipLine(WCHAR* tip, size_t cap, int slot);
void AddOrUpdateTrayIcon(HWND hWnd, BOOL enabled, BOOL isAdd) {
    DnsOverall dns = GetDnsOverall();
    BOOL pending = (InterlockedOr(&g_isProcessingClick, 0) != 0);

    HICON hNewIcon = CreateColoredDotIcon(enabled, dns,
        pending || !InterlockedOr(&g_networkStateKnown, 0));
    if (!hNewIcon) {
        Wh_Log(L"AddOrUpdateTrayIcon: CreateColoredDotIcon failed");
        return;
    }

    // Defer old-icon destruction until after the NIM_MODIFY succeeds
    // so the tray never holds a dangling handle if the update fails.
    HICON hOldIcon = g_currentIcon;
    g_currentIcon = nullptr;

    NOTIFYICONDATAW nid = {sizeof(nid)};
    nid.hWnd = hWnd;
    nid.uID = TRAY_ICON_ID;
    nid.uFlags = NIF_MESSAGE | NIF_TIP | NIF_SHOWTIP | NIF_ICON;
    nid.uCallbackMessage = WM_TRAY_CALLBACK;

    if (InterlockedOr(&g_isProcessingClick, 0) == 1) {
        wsprintfW(nid.szTip, L"Net-Toggle: toggling\u2026");
    } else if (InterlockedOr(&g_isProcessingClick, 0) == 2) {
        wsprintfW(nid.szTip, L"Net-Toggle: refreshing\u2026");
    } else if (!InterlockedOr(&g_networkStateKnown, 0)) {
        wsprintfW(nid.szTip, L"Net-Toggle: adapter state unavailable");
    } else if (!enabled) {
        wsprintfW(nid.szTip, L"Net-Toggle: OFF (click to enable)");
    } else {
        switch (dns) {
            case DNS_OK:       wsprintfW(nid.szTip, L"Net-Toggle: ON | DNS OK"); break;
            case DNS_DEGRADED: wsprintfW(nid.szTip, L"Net-Toggle: ON | DNS degraded"); break;
            case DNS_DOWN:     wsprintfW(nid.szTip, L"Net-Toggle: ON | DNS unreachable"); break;
            case DNS_CHECKING: wsprintfW(nid.szTip, L"Net-Toggle: ON | checking DNS\u2026"); break;
            case DNS_NONE:
            default:           wsprintfW(nid.szTip, L"Net-Toggle: ON"); break;
        }
        if (dns != DNS_NONE) {
            AppendDnsTipLine(nid.szTip, ARRAYSIZE(nid.szTip), 0, L"DNS1");
            AppendDnsTipLine(nid.szTip, ARRAYSIZE(nid.szTip), 1, L"DNS2");
            AppendIcmpTipLine(nid.szTip, ARRAYSIZE(nid.szTip), 0);
            AppendIcmpTipLine(nid.szTip, ARRAYSIZE(nid.szTip), 1);
        }
    }

    nid.hIcon = hNewIcon;
    nid.uFlags |= NIF_GUID;
    nid.guidItem = NETTOGGLE_TRAY_GUID;

    if (isAdd) {
        if (!Shell_NotifyIconW(NIM_ADD, &nid)) {
            LogLastError(L"Shell_NotifyIcon NIM_ADD");
            DestroyIcon(hNewIcon);
            g_currentIcon = hOldIcon;
            return;
        }
        InterlockedExchange(&g_trayIconInstalled, 1);
        NOTIFYICONDATAW nidVer = {sizeof(nidVer)};
        nidVer.hWnd = hWnd;
        nidVer.uID = TRAY_ICON_ID;
        nidVer.uFlags = NIF_GUID;
        nidVer.guidItem = NETTOGGLE_TRAY_GUID;
        nidVer.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, &nidVer);
        if (hOldIcon) DestroyIcon(hOldIcon);
    } else {
        if (!Shell_NotifyIconW(NIM_MODIFY, &nid)) {
            LogLastError(L"Shell_NotifyIcon NIM_MODIFY");
            DestroyIcon(hNewIcon);
            g_currentIcon = hOldIcon;
            return;
        }
        if (hOldIcon) DestroyIcon(hOldIcon);
    }

    g_currentIcon = hNewIcon;
}

// ==============================================================================
// Toggle Logic
// ==============================================================================

DWORD WINAPI WorkerThreadProc(LPVOID lpParam) {
    HRESULT hrCo = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hrCo) && hrCo != RPC_E_CHANGED_MODE) {
        Wh_Log(L"WorkerThread: CoInitializeEx failed (0x%X)", hrCo);
        return 1;
    }
    BOOL enable = (BOOL)(UINT_PTR)lpParam;

    Wh_Log(L"Toggling network adapters: %s", enable ? L"ENABLE" : L"DISABLE");
    LPCWSTR command = enable
        ? L"Get-NetAdapter -Physical -IncludeHidden | Enable-NetAdapter -Confirm:$false -ErrorAction Stop"
        : L"Get-NetAdapter -Physical -IncludeHidden | Disable-NetAdapter -Confirm:$false -ErrorAction Stop";

    BOOL success = RunPowerShellCommand(command);

    if (success) {
        if (enable)
            InterlockedExchange((volatile LONG*)&g_enableGracePeriodUntilTick, GetTickCount() + 12000);
        else
            InterlockedExchange((volatile LONG*)&g_enableGracePeriodUntilTick, 0);
        Wh_Log(L"Network %s operation completed successfully", enable ? L"enable" : L"disable");
    } else {
        Wh_Log(L"Network toggle operation failed or cancelled");
        success = FALSE;
    }

    BOOL actualState = CheckActualNetworkState();
    InterlockedExchange(&g_networkIsUp, actualState ? 1 : 0);

    if (IsWindow(g_trayHwnd)) {
        PostMessageW(g_trayHwnd, WM_UPDATE_TRAY_STATE, (WPARAM)(InterlockedOr(&g_networkIsUp, 0) == 1), 0);
        // After a successful enable the NetWatch poll fallback may miss the state
        // change after the completed command.
        // Trigger a recovery ping explicitly so DNS state updates promptly.
        if (success && enable && InterlockedOr(&g_networkIsUp, 0)) {
            PostMessageW(g_trayHwnd, WM_TRIGGER_PING, 0, 0);
        }
    }
    if (SUCCEEDED(hrCo)) CoUninitialize();
    InterlockedExchange(&g_isProcessingClick, 0);
    return 0;
}

struct AdapterCommand { GUID id; bool enable; };

static DWORD WINAPI AdapterWorkerThreadProc(LPVOID parameter) {
    AdapterCommand command = *reinterpret_cast<AdapterCommand*>(parameter);
    delete reinterpret_cast<AdapterCommand*>(parameter);
    WCHAR guid[40] = {};
    WCHAR script[512] = {};
    bool valid = StringFromGUID2(command.id, guid, ARRAYSIZE(guid)) > 0 &&
        SUCCEEDED(StringCchPrintfW(script, ARRAYSIZE(script),
            L"$a=@(Get-NetAdapter -IncludeHidden | Where-Object {([guid]$_.InterfaceGuid) -eq [guid]'%s'}); "
            L"if($a.Count -ne 1){throw 'Adapter missing or ambiguous'}; "
            L"$a[0] | %s-NetAdapter -Confirm:$false -ErrorAction Stop",
            guid, command.enable ? L"Enable" : L"Disable"));
    bool success = valid && RunPowerShellCommand(script);
    if (!success) Wh_Log(L"Per-adapter operation failed or was cancelled");
    BOOL state = CheckActualNetworkState();
    if (InterlockedOr(&g_networkStateKnown, 0)) InterlockedExchange(&g_networkIsUp, state ? 1 : 0);
    HWND tray = (HWND)g_trayHwnd;
    if (tray && IsWindow(tray)) {
        PostMessageW(tray, WM_UPDATE_TRAY_STATE, (WPARAM)(InterlockedOr(&g_networkIsUp, 0) == 1), 0);
        if (success) PostMessageW(tray, WM_TRIGGER_PING, 0, 0);
    }
    InterlockedExchange(&g_isProcessingClick, 0);
    return 0;
}

static void ProcessAdapterCommand(const AdapterInfo& adapter) {
    if (adapter.admin < 0 || InterlockedCompareExchange(&g_isProcessingClick, 1, 0) != 0) return;
    AdapterCommand* command = new (std::nothrow) AdapterCommand{adapter.id, adapter.admin == 0};
    if (!command) { InterlockedExchange(&g_isProcessingClick, 0); return; }
    DWORD id = 0;
    HANDLE thread = CreateThread(nullptr, 0, AdapterWorkerThreadProc, command, 0, &id);
    if (!thread) {
        delete command;
        InterlockedExchange(&g_isProcessingClick, 0);
        return;
    }
    HANDLE old = (HANDLE)InterlockedExchangePointer((PVOID*)&g_activeWorkerThread, thread);
    if (old) CloseHandle(old);
}

DWORD WINAPI ResetWorkerThreadProc(LPVOID) {
    HRESULT hrCo = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hrCo) && hrCo != RPC_E_CHANGED_MODE) {
        Wh_Log(L"ResetWorkerThread: CoInitializeEx failed (0x%X)", hrCo);
        return 1;
    }
    Wh_Log(L"Executing network blackout reset (disable adapters → flush DNS → re-enable)");

    // The elevated child restores exactly the initially enabled adapters,
    // including when a disable or DNS flush fails.
    LPCWSTR command =
        L"$ids=@(Get-NetAdapter -Physical -IncludeHidden | Where-Object {$_.AdminStatus -eq 'Up'} | ForEach-Object {[string]$_.InterfaceGuid}); "
        L"$restoreFailed=$false; try { "
        L"foreach($id in $ids){ $a=Get-NetAdapter -Physical -IncludeHidden | Where-Object {[string]$_.InterfaceGuid -eq $id}; "
        L"if(!$a){throw 'Adapter disappeared'}; $a | Disable-NetAdapter -Confirm:$false -ErrorAction Stop }; "
        L"Start-Sleep -Seconds 2; ipconfig /flushdns | Out-Null; if($LASTEXITCODE -ne 0){throw 'DNS flush failed'} "
        L"} finally { foreach($id in $ids){ try { $a=Get-NetAdapter -Physical -IncludeHidden | Where-Object {[string]$_.InterfaceGuid -eq $id}; "
        L"if(!$a){throw 'Adapter missing'}; $a | Enable-NetAdapter -Confirm:$false -ErrorAction Stop "
        L"} catch { $restoreFailed=$true; Write-Warning $_ } } }; if($restoreFailed){exit 1}";
    BOOL resetOk = RunPowerShellCommand(command);
    if (resetOk)
        InterlockedExchange((volatile LONG*)&g_enableGracePeriodUntilTick, GetTickCount() + 15000);
    BOOL actualState = CheckActualNetworkState();
    InterlockedExchange(&g_networkIsUp, actualState ? 1 : 0);
    if (IsWindow(g_trayHwnd)) {
        PostMessageW(g_trayHwnd, WM_UPDATE_TRAY_STATE, (WPARAM)(InterlockedOr(&g_networkIsUp, 0) == 1), 0);
        if (resetOk && InterlockedOr(&g_networkIsUp, 0)) {
            // Use 15s settle (wParam=1) to give DHCP/routing time to stabilise
            // after the release/renew before we attempt the DNS ping.
            PostMessageW(g_trayHwnd, WM_TRIGGER_PING, 1, 0);
        }
    }
    if (SUCCEEDED(hrCo)) CoUninitialize();
    InterlockedExchange(&g_isProcessingClick, 0);
    return 0;
}

void ProcessNetworkReset() {
    LONG prev = InterlockedCompareExchange(&g_isProcessingClick, 2, 0);
    if (prev != 0) {
        Wh_Log(L"Already processing a click, ignoring reset request");
        return;
    }

    DWORD now = GetTickCount();
    if (now - g_lastClickTime < CLICK_DEBOUNCE_MS) {
        Wh_Log(L"Click debounced (cooldown active)");
        InterlockedExchange(&g_isProcessingClick, 0);
        return;
    }
    InterlockedExchange(&g_lastClickTime, now);

    Wh_Log(L"Processing network reset (Middle Click)");

    // Show yellow immediately
    if (IsWindow(g_trayHwnd)) {
        PostMessageW(g_trayHwnd, WM_UPDATE_TRAY_STATE, (WPARAM)InterlockedOr(&g_networkIsUp, 0), 0);
    }

    DWORD threadId;
    HANDLE hNewThread = CreateThread(nullptr, 0, ResetWorkerThreadProc, nullptr, 0, &threadId);
    HANDLE hOldThread = (HANDLE)InterlockedExchangePointer((PVOID*)&g_activeWorkerThread, hNewThread);
    if (hOldThread) {
        CloseHandle(hOldThread);
    }
    if (!hNewThread) {
        InterlockedExchange(&g_isProcessingClick, 0);
    }
}

void ProcessTrayClick() {
    LONG prev = InterlockedCompareExchange(&g_isProcessingClick, 1, 0);
    if (prev != 0) {
        Wh_Log(L"Already processing a click, ignoring");
        return;
    }

    DWORD now = GetTickCount();
    if (now - g_lastClickTime < CLICK_DEBOUNCE_MS) {
        Wh_Log(L"Click debounced (cooldown active)");
        InterlockedExchange(&g_isProcessingClick, 0);
        return;
    }
    InterlockedExchange(&g_lastClickTime, now);

    BOOL current = CheckActualNetworkState();
    if (!InterlockedOr(&g_networkStateKnown, 0)) {
        InterlockedExchange(&g_isProcessingClick, 0);
        if (g_trayHwnd && IsWindow(g_trayHwnd))
            MessageBoxW(g_trayHwnd, L"Adapter state is unavailable. Try again after Windows finishes detecting adapters.",
                        L"Net-Toggle", MB_OK | MB_ICONWARNING);
        return;
    }
    InterlockedExchange(&g_networkIsUp, current ? 1 : 0);
    BOOL targetState = !current;
    Wh_Log(L"Processing network toggle click. Target state: %s", targetState ? L"ON" : L"OFF");

    // Show yellow immediately
    if (IsWindow(g_trayHwnd)) {
        PostMessageW(g_trayHwnd, WM_UPDATE_TRAY_STATE, (WPARAM)InterlockedOr(&g_networkIsUp, 0), 0);
    }

    DWORD threadId;
    HANDLE hNewThread = CreateThread(nullptr, 0, WorkerThreadProc, (LPVOID)(UINT_PTR)targetState, 0, &threadId);
    HANDLE hOldThread = (HANDLE)InterlockedExchangePointer((PVOID*)&g_activeWorkerThread, hNewThread);
    if (hOldThread) {
        CloseHandle(hOldThread);
    }
    if (!hNewThread) {
        InterlockedExchange(&g_isProcessingClick, 0);
    }
}

// ==============================================================================
// DNS Ping Handler
// ==============================================================================

static IcmpResult ProbeIcmp(DWORD ip, int slot, LONG generation) {
    IcmpResult result = {ip, generation, slot, -1, 0};
    HANDLE handle = IcmpCreateFile();
    if (handle == INVALID_HANDLE_VALUE) return result;
    BYTE request[8] = {'N', 'e', 't', 'T', 'o', 'g', 'g', 'l'};
    alignas(ICMP_ECHO_REPLY) BYTE reply[sizeof(ICMP_ECHO_REPLY) + sizeof(request) + 8] = {};
    DWORD count = IcmpSendEcho(handle, ip, request, sizeof(request), nullptr,
                               reply, sizeof(reply), 1000);
    DWORD error = count ? NO_ERROR : GetLastError();
    if (count > 0) {
        const auto* echo = reinterpret_cast<const ICMP_ECHO_REPLY*>(reply);
        result.status = echo->Status == IP_SUCCESS ? 1 : 0;
        if (result.status == 1) result.rtt = echo->RoundTripTime;
    } else if (error == IP_REQ_TIMED_OUT || error == IP_DEST_NET_UNREACHABLE ||
               error == IP_DEST_HOST_UNREACHABLE || error == IP_DEST_PROT_UNREACHABLE ||
               error == IP_DEST_PORT_UNREACHABLE) {
        result.status = 0;
    }
    IcmpCloseHandle(handle);
    return result;
}

static void AppendIcmpTipLine(WCHAR* tip, size_t cap, int slot) {
    LONG ip = InterlockedOr(&g_dnsIp[slot], 0);
    if (!ip || (slot == 1 && ip == InterlockedOr(&g_dnsIp[0], 0))) return;
    IcmpHistory history;
    AcquireSRWLockShared(&g_icmpLock);
    history = g_icmpHistory[slot];
    ReleaseSRWLockShared(&g_icmpLock);
    if (history.ip != (DWORD)ip) return;
    size_t len = wcslen(tip);
    if (len + 35 >= cap) return;
    if (history.status < 0) {
        swprintf_s(tip + len, cap - len, L"\nICMP%d unavailable", slot + 1);
        return;
    }
    int lost = 0;
    for (int i = 0; i < history.count; i++) lost += history.samples[i];
    if (history.status == 1)
        swprintf_s(tip + len, cap - len, L"\nICMP%d %s%lums, loss %d/%d",
                   slot + 1, history.rtt == 0 ? L"<" : L"", history.rtt == 0 ? 1UL : history.rtt,
                   lost, history.count);
    else
        swprintf_s(tip + len, cap - len, L"\nICMP%d timeout, loss %d/%d", slot + 1, lost, history.count);
}

static void ResetIcmpHistory() {
    AcquireSRWLockExclusive(&g_icmpLock);
    g_icmpHistory[0] = IcmpHistory{};
    g_icmpHistory[1] = IcmpHistory{};
    ReleaseSRWLockExclusive(&g_icmpLock);
}

static void RecordIcmpResult(const IcmpResult& result) {
    AcquireSRWLockExclusive(&g_icmpLock);
    IcmpHistory& history = g_icmpHistory[result.slot];
    if (history.ip != result.ip) history = IcmpHistory{};
    history.ip = result.ip;
    history.status = result.status;
    history.rtt = result.rtt;
    if (result.status >= 0) {
        history.samples[history.next] = result.status == 1 ? 0 : 1;
        history.next = (history.next + 1) % ARRAYSIZE(history.samples);
        if (history.count < (int)ARRAYSIZE(history.samples)) history.count++;
    }
    ReleaseSRWLockExclusive(&g_icmpLock);
}

DWORD WINAPI DnsPingWorkerProc(LPVOID) {
    LONG generation = InterlockedOr(&g_dnsGeneration, 0);
    LONG networkGeneration = InterlockedOr(&g_networkGeneration, 0);
    LONG ips[2] = {InterlockedOr(&g_dnsIp[0], 0), InterlockedOr(&g_dnsIp[1], 0)};
    LONG methods[2] = {InterlockedOr(&g_dnsProbe[0], 0), InterlockedOr(&g_dnsProbe[1], 0)};
    if ((generation & 1) || generation != InterlockedOr(&g_dnsGeneration, 0)) {
        InterlockedExchange(&g_dnsWorkerRunning, 0);
        return 0;
    }
    // Probe each configured slot in priority order. Results publish per slot
    // so the tooltip can show ✓/✗ per server and GetDnsOverall() can derive
    // OK / DEGRADED / DOWN.
    for (int i = 0; i < 2; i++) {
        LONG ip = ips[i];
        if (ip == 0) {
            InterlockedExchange(&g_dnsUp[i], -1);
            continue;
        }
        // Bail out if the network dropped or the mod is unloading mid-pass.
        if (InterlockedOr(&g_networkIsUp, 0) == 0) break;
        HANDLE hShutdown = (HANDLE)InterlockedCompareExchangePointer((PVOID*)&g_shutdownEvent, nullptr, nullptr);
        if (hShutdown && WaitForSingleObject(hShutdown, 0) == WAIT_OBJECT_0) break;

        BOOL up = ProbeDnsServer((DWORD)ip, methods[i]);
        if (generation != InterlockedOr(&g_dnsGeneration, 0) ||
            networkGeneration != InterlockedOr(&g_networkGeneration, 0) ||
            InterlockedOr(&g_networkIsUp, 0) == 0) break;
        InterlockedExchange(&g_dnsUp[i], up ? 1 : 0);
    }

    for (int i = 0; i < 2; i++) {
        if (!ips[i] || (i == 1 && ips[1] == ips[0])) continue;
        HANDLE stop = (HANDLE)InterlockedCompareExchangePointer((PVOID*)&g_shutdownEvent, nullptr, nullptr);
        if (generation != InterlockedOr(&g_dnsGeneration, 0) ||
            networkGeneration != InterlockedOr(&g_networkGeneration, 0) ||
            InterlockedOr(&g_networkIsUp, 0) == 0 ||
            (stop && WaitForSingleObject(stop, 0) == WAIT_OBJECT_0)) break;
        IcmpResult value = ProbeIcmp((DWORD)ips[i], i, generation);
        if (generation != InterlockedOr(&g_dnsGeneration, 0) ||
            networkGeneration != InterlockedOr(&g_networkGeneration, 0) ||
            InterlockedOr(&g_networkIsUp, 0) == 0) break;
        RecordIcmpResult(value);
    }

    if (IsWindow(g_trayHwnd)) {
        PostMessageW(g_trayHwnd, WM_UPDATE_TRAY_STATE,
                     (WPARAM)(InterlockedOr(&g_networkIsUp, 0) == 1), 0);
    }
    InterlockedExchange(&g_dnsWorkerRunning, 0);
    return 0;
}

void OnDnsPingTimer(HWND hWnd) {
    if (!AnyDnsConfigured()) return;

    if (InterlockedOr(&g_networkIsUp, 0) == 0) {
        Wh_Log(L"Network is OFF, skipping DNS check");
        // Status is unknowable while offline; mark unchecked so the icon shows
        // "checking" (not a stale ✗) when the network comes back.
        InterlockedExchange(&g_dnsUp[0], -1);
        InterlockedExchange(&g_dnsUp[1], -1);
        PostMessageW(hWnd, WM_UPDATE_TRAY_STATE, 0, 0);
        return;
    }

    if (InterlockedCompareExchange(&g_dnsWorkerRunning, 1, 0) != 0) {
        Wh_Log(L"DNS check already in progress, skipping");
        return;
    }

    Wh_Log(L"Triggering DNS reachability check...");
    HANDLE hThread = CreateThread(nullptr, 0, DnsPingWorkerProc, nullptr, 0, nullptr);
    if (!hThread) {
        InterlockedExchange(&g_dnsWorkerRunning, 0);
    } else {
        // Track the handle so mod unload can wait for an in-flight check.
        HANDLE hOld = (HANDLE)InterlockedExchangePointer((PVOID*)&g_dnsWorkerThread, hThread);
        if (hOld) CloseHandle(hOld);
    }
}

// ==============================================================================
// Settings
// ==============================================================================

// Parses one "server + check method" settings pair into a probe slot.
static void LoadDnsSlotSetting(int slot, LPCWSTR serverKey, LPCWSTR probeKey) {
    DWORD newIp = 0;
    auto server = WindhawkUtils::StringSetting::make(serverKey);
    if (server.get()[0]) {
        if (InetPtonW(AF_INET, server.get(), &newIp) != 1) {
            Wh_Log(L"Invalid DNS server IP '%s' — slot %d disabled", server.get(), slot + 1);
            newIp = 0;
        } else {
            Wh_Log(L"DNS slot %d: %s", slot + 1, server.get());
        }
    }

    LONG method = PROBE_UDP_DNS;
    auto probe = WindhawkUtils::StringSetting::make(probeKey);
    if (wcscmp(probe.get(), L"tcp") == 0)      method = PROBE_TCP_53;
    else if (wcscmp(probe.get(), L"dot") == 0) method = PROBE_TCP_853;
    else if (wcscmp(probe.get(), L"doh") == 0) method = PROBE_TCP_443;

    InterlockedExchange(&g_dnsIp[slot], (LONG)newIp);
    InterlockedExchange(&g_dnsProbe[slot], method);
    InterlockedExchange(&g_dnsUp[slot], -1);  // force a fresh probe result
}

static void LoadDnsSettings() {
    InterlockedIncrement(&g_dnsGeneration);  // odd while the pair is changing
    LoadDnsSlotSetting(0, L"dnsServer", L"dnsProbe");
    LoadDnsSlotSetting(1, L"dnsServer2", L"dnsProbe2");

    // An identical duplicate adds no signal — keep only the primary copy.
    if (InterlockedOr(&g_dnsIp[1], 0) != 0 &&
        InterlockedOr(&g_dnsIp[1], 0) == InterlockedOr(&g_dnsIp[0], 0) &&
        InterlockedOr(&g_dnsProbe[1], 0) == InterlockedOr(&g_dnsProbe[0], 0)) {
        Wh_Log(L"Secondary DNS duplicates primary — ignoring secondary");
        InterlockedExchange(&g_dnsIp[1], 0);
    }

    if (!AnyDnsConfigured()) {
        Wh_Log(L"No DNS server configured — DNS monitoring disabled");
    }

    int intervalSec = Wh_GetIntSetting(L"pingInterval");
    if (intervalSec < MIN_PING_INTERVAL_SEC) intervalSec = MIN_PING_INTERVAL_SEC;
    g_pingIntervalMs = (DWORD)intervalSec * 1000;
    InterlockedIncrement(&g_dnsGeneration);
}

// ==============================================================================
// Feature D — Right-Click Context Menu
// ==============================================================================

static bool IsSystemDarkMode() {
    DWORD value = 1, size = sizeof(value);
    RegGetValueW(HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"AppsUseLightTheme", RRF_RT_REG_DWORD, nullptr, &value, &size);
    return value == 0;
}

static void ApplyContextMenuTheme(HWND hWnd, bool dark) {
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) return;
    using Fn135 = int(WINAPI*)(int);
    using Fn133 = bool(WINAPI*)(HWND, bool);
    using Fn136 = void(WINAPI*)();
    if (auto f = (Fn135)GetProcAddress(ux, MAKEINTRESOURCEA(135))) f(dark ? 2 : 0);
    if (auto f = (Fn133)GetProcAddress(ux, MAKEINTRESOURCEA(133))) f(hWnd, dark);
    if (auto f = (Fn136)GetProcAddress(ux, MAKEINTRESOURCEA(136))) f();
}

static DWORD WINAPI WifiWorkerThreadProc(LPVOID lpParam) {
    HRESULT hrCo = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hrCo) && hrCo != RPC_E_CHANGED_MODE) {
        Wh_Log(L"WifiWorkerThread: CoInitializeEx failed (0x%X)", hrCo);
        return 1;
    }
    BOOL enable = (BOOL)(UINT_PTR)lpParam;

    Wh_Log(L"Toggling Wi-Fi adapters: %s", enable ? L"ENABLE" : L"DISABLE");
    LPCWSTR command = enable
        ? L"Get-NetAdapter -Physical -IncludeHidden | Where-Object { $_.PhysicalMediaType -eq 'Native 802.11' -or $_.MediaType -eq 'Native 802.11' -or $_.InterfaceDescription -match 'Wi-Fi|Wireless|802\\.11' -or $_.Name -match 'Wi-Fi|Wireless' } | Enable-NetAdapter -Confirm:$false -ErrorAction Stop"
        : L"Get-NetAdapter -Physical -IncludeHidden | Where-Object { $_.PhysicalMediaType -eq 'Native 802.11' -or $_.MediaType -eq 'Native 802.11' -or $_.InterfaceDescription -match 'Wi-Fi|Wireless|802\\.11' -or $_.Name -match 'Wi-Fi|Wireless' } | Disable-NetAdapter -Confirm:$false -ErrorAction Stop";

    BOOL success = RunPowerShellCommand(command);

    if (success) {
        if (enable)
            InterlockedExchange((volatile LONG*)&g_enableGracePeriodUntilTick, GetTickCount() + 12000);
        else
            InterlockedExchange((volatile LONG*)&g_enableGracePeriodUntilTick, 0);
        Wh_Log(L"Wi-Fi adapter %s operation completed successfully", enable ? L"enable" : L"disable");
    } else {
        Wh_Log(L"Wi-Fi adapter toggle operation failed or cancelled");
    }

    BOOL actualState = CheckActualNetworkState();
    InterlockedExchange(&g_networkIsUp, actualState ? 1 : 0);

    if (IsWindow(g_trayHwnd)) {
        PostMessageW(g_trayHwnd, WM_UPDATE_TRAY_STATE, (WPARAM)(InterlockedOr(&g_networkIsUp, 0) == 1), 0);
        if (success && enable && InterlockedOr(&g_networkIsUp, 0)) {
            PostMessageW(g_trayHwnd, WM_TRIGGER_PING, 0, 0);
        }
    }
    if (SUCCEEDED(hrCo)) CoUninitialize();
    InterlockedExchange(&g_isProcessingClick, 0);
    return 0;
}

static void ProcessWifiToggle(BOOL enable) {
    if (InterlockedCompareExchange(&g_isProcessingClick, 1, 0) != 0) return;
    Wh_Log(L"Processing Wi-Fi toggle click. Target state: %s", enable ? L"ENABLE" : L"DISABLE");

    DWORD threadId = 0;
    HANDLE hNewThread = CreateThread(nullptr, 0, WifiWorkerThreadProc, (LPVOID)(UINT_PTR)enable, 0, &threadId);
    HANDLE hOldThread = (HANDLE)InterlockedExchangePointer((PVOID*)&g_activeWorkerThread, hNewThread);
    if (hOldThread) {
        CloseHandle(hOldThread);
    }
    if (!hNewThread) {
        InterlockedExchange(&g_isProcessingClick, 0);
    }
}

static HMENU g_activeAdapterMenu = nullptr;
static std::vector<AdapterInfo> g_currentPhysicalAdapters;

void ShowContextMenu(HWND hWnd) {
    HMENU hMenu = CreatePopupMenu();
    BOOL netUp = CheckActualNetworkState();
    if (InterlockedOr(&g_networkStateKnown, 0)) InterlockedExchange(&g_networkIsUp, netUp ? 1 : 0);
    AppendMenuW(hMenu, MF_STRING | (InterlockedOr(&g_networkStateKnown, 0) ? 0 : MF_GRAYED),
                MENU_TOGGLE_NET, InterlockedOr(&g_networkStateKnown, 0) ?
                (netUp ? L"Disable physical adapters" : L"Enable physical adapters") : L"Network state unavailable");

    std::vector<AdapterInfo> adapters;
    std::vector<AdapterInfo> physicalAdapters;
    bool hasWifi = false;
    bool wifiEnabled = false;
    bool wifiKnown = false;

    if (EnumerateAdapters(adapters)) {
        for (const auto& a : adapters) {
            if (a.physical) {
                physicalAdapters.push_back(a);
                if (a.isWifi) {
                    hasWifi = true;
                    if (a.admin == 1) wifiEnabled = true;
                    if (a.admin >= 0) wifiKnown = true;
                }
            }
        }

        HMENU adapterMenu = CreatePopupMenu();
        for (size_t i = 0; i < physicalAdapters.size() && i < 100; ++i) {
            WCHAR label[180];
            swprintf_s(label, L"%s  %s", physicalAdapters[i].admin < 0 ? L"[?]" :
                physicalAdapters[i].admin ? L"[On]" : L"[Off]",
                physicalAdapters[i].name[0] ? physicalAdapters[i].name : L"Unnamed adapter");
            AppendMenuW(adapterMenu, MF_STRING | (physicalAdapters[i].admin < 0 ? MF_GRAYED : 0),
                        MENU_ADAPTER_FIRST + (UINT)i, label);
        }
        if (physicalAdapters.empty()) {
            AppendMenuW(adapterMenu, MF_STRING | MF_GRAYED, 0, L"No physical adapters found");
        }
        AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)adapterMenu, L"Adapters");
        g_activeAdapterMenu = adapterMenu;
        g_currentPhysicalAdapters = physicalAdapters;
    }

    UINT wifiFlags = MF_STRING;
    LPCWSTR wifiLabel = L"Disable Wifi Adapters";
    if (!hasWifi) {
        wifiFlags |= MF_GRAYED;
        wifiLabel = L"No Wi-Fi adapters";
    } else if (!wifiKnown) {
        wifiFlags |= MF_GRAYED;
        wifiLabel = L"Wi-Fi state unavailable";
    } else if (wifiEnabled) {
        wifiLabel = L"Disable Wifi Adapters";
    } else {
        wifiLabel = L"Enable Wifi Adapters";
    }
    AppendMenuW(hMenu, wifiFlags, MENU_TOGGLE_WIFI, wifiLabel);

    AppendMenuW(hMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(hMenu, MF_STRING, MENU_NET_SETTINGS, L"Open Network Settings");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, nullptr);

    MENUITEMINFOW miiWH = {sizeof(miiWH)};
    miiWH.fMask      = MIIM_ID | MIIM_STRING | MIIM_BITMAP;
    miiWH.wID        = MENU_OPEN_WINDHAWK;
    miiWH.dwTypeData = (LPWSTR)L"Open Windhawk";
    miiWH.hbmpItem   = g_hWindHawkBmp;
    InsertMenuItemW(hMenu, (UINT)-1, TRUE, &miiWH);

    POINT pt; GetCursorPos(&pt);
    bool dark = IsSystemDarkMode();
    ApplyContextMenuTheme(hWnd, dark);
    SetForegroundWindow(hWnd);
    int cmd = TrackPopupMenu(hMenu,
        TPM_RETURNCMD | TPM_RIGHTBUTTON | TPM_BOTTOMALIGN | TPM_RIGHTALIGN,
        pt.x, pt.y, 0, hWnd, nullptr);
    PostMessageW(hWnd, WM_NULL, 0, 0);
    DestroyMenu(hMenu);
    g_activeAdapterMenu = nullptr;

    if (cmd >= MENU_ADAPTER_FIRST && cmd < MENU_ADAPTER_FIRST + (int)g_currentPhysicalAdapters.size()) {
        ProcessAdapterCommand(g_currentPhysicalAdapters[cmd - MENU_ADAPTER_FIRST]);
        return;
    }

    switch (cmd) {
        case MENU_TOGGLE_NET:
            ProcessTrayClick();
            break;
        case MENU_NET_SETTINGS:
            ShellExecuteW(nullptr, L"open", L"ms-settings:network",
                          nullptr, nullptr, SW_SHOW);
            break;
        case MENU_TOGGLE_WIFI:
            ProcessWifiToggle(!wifiEnabled);
            break;
        case MENU_OPEN_WINDHAWK: {
            SHELLEXECUTEINFOW sei = {sizeof(sei)};
            sei.lpFile = g_windhawkPath;
            sei.nShow  = SW_SHOWNORMAL;
            ShellExecuteExW(&sei);
            break;
        }
    }
}

// ==============================================================================
// Tray Window
// ==============================================================================

LRESULT CALLBACK TrayWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_TRAY_CALLBACK) {
        if (LOWORD(lParam) == WM_LBUTTONDBLCLK) {
            ProcessTrayClick();
        } else if (LOWORD(lParam) == WM_RBUTTONUP) {
            ShowContextMenu(hWnd);
        } else if (LOWORD(lParam) == WM_MBUTTONUP) {
            ProcessNetworkReset();
        }
        return 0;
    } else if (msg == WM_INITMENUPOPUP) {
        HMENU hPopup = (HMENU)wParam;
        if (hPopup && hPopup == g_activeAdapterMenu && !HIWORD(lParam)) {
            std::vector<AdapterInfo> freshAdapters;
            if (EnumerateAdapters(freshAdapters)) {
                g_currentPhysicalAdapters.clear();
                for (const auto& a : freshAdapters) {
                    if (a.physical) g_currentPhysicalAdapters.push_back(a);
                }
                for (size_t i = 0; i < g_currentPhysicalAdapters.size() && i < 100; ++i) {
                    WCHAR label[180];
                    swprintf_s(label, L"%s  %s", g_currentPhysicalAdapters[i].admin < 0 ? L"[?]" :
                        g_currentPhysicalAdapters[i].admin ? L"[On]" : L"[Off]",
                        g_currentPhysicalAdapters[i].name[0] ? g_currentPhysicalAdapters[i].name : L"Unnamed adapter");
                    ModifyMenuW(hPopup, MENU_ADAPTER_FIRST + (UINT)i,
                                MF_BYCOMMAND | MF_STRING | (g_currentPhysicalAdapters[i].admin < 0 ? MF_GRAYED : 0),
                                MENU_ADAPTER_FIRST + (UINT)i, label);
                }
            }
        }
        return 0;
    } else if (msg == WM_UPDATE_TRAY_STATE) {
        LONG state = wParam ? 1 : 0;
        if (InterlockedExchange(&g_lastNotifiedNetworkState, state) != state)
            InterlockedIncrement(&g_networkGeneration);
        if (!wParam) ResetIcmpHistory();
        AddOrUpdateTrayIcon(hWnd, (BOOL)wParam, FALSE);
        return 0;
    } else if (msg == WM_TRIGGER_PING) {
        // wParam=0: normal re-enable — 6s settle for DHCP/init.
        // wParam=1: post-blackout-reset — 15s settle; adapter cycle + DHCP needs more time.
        UINT settleMs = (wParam == 1) ? 15000 : 6000;
        SetTimer(hWnd, DNS_RECOVERY_TIMER_ID, settleMs, nullptr);
        return 0;
    } else if (msg == WM_SETTINGS_CHANGED) {
        // Re-read settings on the tray thread
        LoadDnsSettings();
        ResetIcmpHistory();

        KillTimer(hWnd, DNS_PING_TIMER_ID);
        if (AnyDnsConfigured()) {
            SetTimer(hWnd, DNS_PING_TIMER_ID, g_pingIntervalMs, nullptr);
            // Immediate first check
            OnDnsPingTimer(hWnd);
        }
        AddOrUpdateTrayIcon(hWnd, (BOOL)(InterlockedOr(&g_networkIsUp, 0) == 1), FALSE);
        return 0;
    } else if (msg == WM_TIMER) {
        if (wParam == DNS_PING_TIMER_ID) {
            OnDnsPingTimer(hWnd);
        } else if (wParam == DNS_RECOVERY_TIMER_ID) {
            KillTimer(hWnd, DNS_RECOVERY_TIMER_ID);
            OnDnsPingTimer(hWnd);
        }
        return 0;
    } else if (msg == WM_CLOSE) {
        KillTimer(hWnd, DNS_PING_TIMER_ID);
        KillTimer(hWnd, DNS_RECOVERY_TIMER_ID);
        NOTIFYICONDATAW nid = {sizeof(nid)};
        nid.hWnd = hWnd;
        nid.uID = TRAY_ICON_ID;
        nid.uFlags = NIF_GUID;
        nid.guidItem = NETTOGGLE_TRAY_GUID;
        Shell_NotifyIconW(NIM_DELETE, &nid);
        DestroyWindow(hWnd);
        return 0;
    } else if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    } else if (msg == g_taskbarCreatedMsg && g_taskbarCreatedMsg != 0) {
        Wh_Log(L"Explorer restarted — re-adding tray icon");
        AddOrUpdateTrayIcon(hWnd, (BOOL)(InterlockedOr(&g_networkIsUp, 0) == 1), TRUE);
        if (AnyDnsConfigured()) OnDnsPingTimer(hWnd);  // verify state asynchronously
        return 0;
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

// ==============================================================================
// Feature G — Event-Driven Adapter Watch Thread
// ==============================================================================

DWORD WINAPI NetWatchThreadProc(LPVOID) {
    Wh_Log(L"NetWatch thread started");
    HANDLE hEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!hEvent) {
        Wh_Log(L"NetWatch: CreateEvent failed");
        return 1;
    }

    while (true) {
        HANDLE notifyHandle = nullptr;
        OVERLAPPED ov = {};
        ov.hEvent = hEvent;

        DWORD nacRet = NotifyAddrChange(&notifyHandle, &ov);
        if (nacRet != ERROR_IO_PENDING && nacRet != NO_ERROR) {
            Wh_Log(L"NetWatch: NotifyAddrChange failed (%d) — polling for %ds then retrying",
                   nacRet, (NETWATCH_POLL_RETRIES * NETWATCH_POLL_INTERVAL) / 1000);
            // Bounded fallback: poll NETWATCH_POLL_RETRIES × NETWATCH_POLL_INTERVAL,
            // then retry NotifyAddrChange so event-driven mode is restored after adapters recover.
            // Skip polls while a toggle/reset is in flight to avoid Yellow→Red flicker.
            bool shutdown = false;
            for (DWORD i = 0; i < NETWATCH_POLL_RETRIES; i++) {
                HANDLE hShutdown = (HANDLE)InterlockedCompareExchangePointer((PVOID*)&g_shutdownEvent, nullptr, nullptr);
                DWORD r = hShutdown ? WaitForSingleObject(hShutdown, NETWATCH_POLL_INTERVAL) : WAIT_TIMEOUT;
                if (r == WAIT_OBJECT_0) { shutdown = true; break; }
                if (InterlockedOr(&g_isProcessingClick, 0) != 0) continue;
                BOOL newState = CheckActualNetworkState();
                LONG oldState = InterlockedOr(&g_networkIsUp, 0);
                InterlockedExchange(&g_networkIsUp, newState ? 1 : 0);
                if (newState != (oldState == 1) && IsWindow(g_trayHwnd)) {
                    PostMessageW(g_trayHwnd, WM_UPDATE_TRAY_STATE, (WPARAM)newState, 0);
                    if (newState) PostMessageW(g_trayHwnd, WM_TRIGGER_PING, 0, 0);
                }
            }
            if (shutdown) {
                CloseHandle(hEvent);
                return 0;
            }
            Wh_Log(L"NetWatch: retrying NotifyAddrChange after polling fallback");
            continue;
        }

        if (nacRet == NO_ERROR) {
            if (InterlockedOr(&g_isProcessingClick, 0) == 0) {
                BOOL newState = CheckActualNetworkState();
                InterlockedExchange(&g_networkIsUp, newState ? 1 : 0);
                if (IsWindow(g_trayHwnd)) {
                    PostMessageW(g_trayHwnd, WM_UPDATE_TRAY_STATE, (WPARAM)newState, 0);
                    if (newState) PostMessageW(g_trayHwnd, WM_TRIGGER_PING, 0, 0);
                }
            }
            HANDLE stop = (HANDLE)InterlockedCompareExchangePointer((PVOID*)&g_shutdownEvent, nullptr, nullptr);
            if (stop && WaitForSingleObject(stop, 1000) == WAIT_OBJECT_0) break;
            continue;
        }
        HANDLE hSd = (HANDLE)InterlockedCompareExchangePointer((PVOID*)&g_shutdownEvent, nullptr, nullptr);
        HANDLE waits[2] = { hEvent, hSd };
        DWORD r = WAIT_TIMEOUT;
        while (true) {
            r = WaitForMultipleObjects(2, waits, FALSE, 5000);
            if (r != WAIT_TIMEOUT) break;
            HANDLE hCheck = (HANDLE)InterlockedCompareExchangePointer((PVOID*)&g_shutdownEvent, nullptr, nullptr);
            if (hCheck && WaitForSingleObject(hCheck, 0) == WAIT_OBJECT_0) {
                r = WAIT_OBJECT_0 + 1; // treat as shutdown
                break;
            }
        }

        if (r == WAIT_OBJECT_0) {
            // Adapter state changed externally.
            // Skip while a toggle/reset is in flight — the worker owns g_networkIsUp
            // during that window and will post the definitive state when done.
            // NotifyAddrChange owns this handle; the event is ours.
            if (InterlockedOr(&g_isProcessingClick, 0) == 0) {
                BOOL newState = CheckActualNetworkState();
                InterlockedExchange(&g_networkIsUp, newState ? 1 : 0);
                if (IsWindow(g_trayHwnd)) {
                    PostMessageW(g_trayHwnd, WM_UPDATE_TRAY_STATE, (WPARAM)newState, 0);
                    if (newState) {
                        PostMessageW(g_trayHwnd, WM_TRIGGER_PING, 0, 0);
                    }
                }
            }
        } else {
            // Shutdown signal
            if (nacRet == ERROR_IO_PENDING) {
                CancelIPChangeNotify(&ov);
                // Keep OVERLAPPED and its event alive until cancellation completes.
                WaitForSingleObject(hEvent, INFINITE);
            }
            break;
        }
    }

    CloseHandle(hEvent);
    Wh_Log(L"NetWatch thread exiting");
    return 0;
}

// ==============================================================================
// Tray Thread
// ==============================================================================

DWORD WINAPI TrayThreadProc(LPVOID) {
    Wh_Log(L"Tray thread started");

    HRESULT hrCo = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hrCo) && hrCo != RPC_E_CHANGED_MODE) {
        Wh_Log(L"TrayThread: CoInitializeEx failed (0x%X)", hrCo);
        return 1;
    }
    g_taskbarCreatedMsg = RegisterWindowMessageW(L"TaskbarCreated");

    BOOL initialState = CheckActualNetworkState();
    InterlockedExchange(&g_networkIsUp, initialState ? 1 : 0);

    WNDCLASSW wc = {};
    wc.lpfnWndProc = TrayWndProc;
    wc.hInstance = g_hInstance;
    wc.lpszClassName = L"NetToggleWindowClass";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    if (!RegisterClassW(&wc)) {
        LogLastError(L"RegisterClassW");
        if (SUCCEEDED(hrCo)) CoUninitialize();
        return 1;
    }

    HWND hWnd = CreateWindowExW(
        WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
        wc.lpszClassName,
        L"Net-Toggle",
        WS_POPUP,
        0, 0, 1, 1,
        nullptr, nullptr, g_hInstance, nullptr
    );

    if (!hWnd) {
        LogLastError(L"CreateWindowExW");
        UnregisterClassW(wc.lpszClassName, g_hInstance);
        if (SUCCEEDED(hrCo)) CoUninitialize();
        return 1;
    }

    InterlockedExchangePointer((PVOID*)&g_trayHwnd, hWnd);

    // Unique AUMID so the OS doesn't group this icon with Windhawk's main window.
    IPropertyStore* pps = nullptr;
    if (SUCCEEDED(SHGetPropertyStoreForWindow(hWnd, IID_PPV_ARGS(&pps)))) {
        PROPVARIANT var;
        PropVariantInit(&var);
        var.vt = VT_LPWSTR;
        var.pwszVal = (LPWSTR)CoTaskMemAlloc(MAX_PATH * sizeof(WCHAR));
        if (var.pwszVal) {
            wcscpy_s(var.pwszVal, MAX_PATH, L"BlackPaw.NetToggle");
            pps->SetValue(PKEY_AppUserModel_ID, var);
            CoTaskMemFree(var.pwszVal);
        }
        pps->Commit();
        pps->Release();
    }

    AddOrUpdateTrayIcon(hWnd, initialState, TRUE);
    Wh_Log(L"Tray icon installed. Initial state: %s", initialState ? L"ON" : L"OFF");

    // Start DNS check timer if configured
    if (AnyDnsConfigured()) {
        SetTimer(hWnd, DNS_PING_TIMER_ID, g_pingIntervalMs, nullptr);
        // Immediate first check
        OnDnsPingTimer(hWnd);
    }

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    Wh_Log(L"Tray message loop ending");

    HICON oldIcon = (HICON)InterlockedExchangePointer((PVOID*)&g_currentIcon, nullptr);
    if (oldIcon) {
        DestroyIcon(oldIcon);
    }

    UnregisterClassW(wc.lpszClassName, g_hInstance);
    InterlockedExchange(&g_trayIconInstalled, 0);
    InterlockedExchangePointer((PVOID*)&g_trayHwnd, nullptr);
    if (SUCCEEDED(hrCo)) CoUninitialize();

    return 0;
}

// ==============================================================================
// TOOL MOD IMPLEMENTATION
// ==============================================================================

BOOL WhTool_ModInit() {
    Wh_Log(L"Net-Toggle Mod Init");

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        Wh_Log(L"WSAStartup failed");
        return FALSE;
    }

    g_hInstance = GetModuleHandleW(nullptr);
    if (!g_hInstance) {
        Wh_Log(L"Failed to get module handle");
        return FALSE;
    }

    Wh_Log(L"Using WiFi-style arc icon");

    // Enable dark mode for context menus app-wide
    {
        HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
        if (ux) {
            using FnSetMode = void(WINAPI*)(int);
            using FnAllow   = bool(WINAPI*)(bool);
            if (auto f = (FnSetMode)GetProcAddress(ux, MAKEINTRESOURCEA(135)))
                f(1);
            else if (auto f = (FnAllow)GetProcAddress(ux, MAKEINTRESOURCEA(132)))
                f(true);
        }
    }

    // Windhawk executable path (for "Open Windhawk" menu item)
    switch (GetModuleFileNameW(nullptr, g_windhawkPath, ARRAYSIZE(g_windhawkPath))) {
        case 0:
        case ARRAYSIZE(g_windhawkPath):
            Wh_Log(L"GetModuleFileName failed");
            return FALSE;
    }

    // Load Windhawk icon from ddores.dll for the context menu
    UINT sysLen = GetSystemDirectoryW(g_ddoresDllPath, MAX_PATH);
    if (sysLen > 0 && sysLen < MAX_PATH - 12)
        lstrcatW(g_ddoresDllPath, L"\\ddores.dll");
    else
        lstrcpyW(g_ddoresDllPath, L"ddores.dll");

    int whIconIndices[] = {98, 94, 95, 6};
    for (int idx : whIconIndices) {
        ExtractIconExW(g_ddoresDllPath, idx, nullptr, &g_hWindHawkIcon, 1);
        if (g_hWindHawkIcon) break;
    }
    if (g_hWindHawkIcon) {
        ICONINFO ii = {};
        if (GetIconInfo(g_hWindHawkIcon, &ii)) {
            g_hWindHawkBmp = ii.hbmColor ? ii.hbmColor : ii.hbmMask;
            if (ii.hbmColor && ii.hbmMask) DeleteObject(ii.hbmMask);
        }
    }

    // Read initial settings
    LoadDnsSettings();

    // Create shutdown event (manual-reset, initially non-signalled)
    g_shutdownEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_shutdownEvent) {
        LogLastError(L"CreateEvent(shutdownEvent)");
        return FALSE;
    }

    // Start tray thread
    DWORD threadId = 0;
    g_trayThread = CreateThread(nullptr, 0, TrayThreadProc, nullptr, 0, &threadId);
    if (!g_trayThread) {
        LogLastError(L"CreateThread(tray)");
        CloseHandle(g_shutdownEvent);
        g_shutdownEvent = nullptr;
        return FALSE;
    }

    // Start net watch thread
    g_netWatchThread = CreateThread(nullptr, 0, NetWatchThreadProc, nullptr, 0, &threadId);
    if (!g_netWatchThread) {
        LogLastError(L"CreateThread(netWatch)");
        // Non-fatal — notify watch is a best-effort feature
        g_netWatchThread = nullptr;
    }

    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (IsWindow(g_trayHwnd)) {
        PostMessageW(g_trayHwnd, WM_SETTINGS_CHANGED, 0, 0);
    }
}

void WhTool_ModUninit() {
    Wh_Log(L"Net-Toggle Mod Uninit");

    // Step 1: signal shutdown
    if (g_shutdownEvent) {
        SetEvent(g_shutdownEvent);
    }

    // Step 2: close tray window (triggers PostQuitMessage)
    if (IsWindow(g_trayHwnd)) {
        PostMessageW(g_trayHwnd, WM_CLOSE, 0, 0);
    }

    // Step 3: wait for threads
    // Atomically take ownership of the worker handles so a concurrent
    // ProcessTrayClick/ProcessNetworkReset/OnDnsPingTimer on the tray thread
    // can't be racing us on the same handle (each does its own
    // InterlockedExchangePointer when spawning a new worker).
    HANDLE hActiveWorker = (HANDLE)InterlockedExchangePointer((PVOID*)&g_activeWorkerThread, nullptr);
    HANDLE hDnsWorker    = (HANDLE)InterlockedExchangePointer((PVOID*)&g_dnsWorkerThread, nullptr);

    HANDLE waitThreads[4] = {};
    DWORD waitCount = 0;
    if (g_trayThread) waitThreads[waitCount++] = g_trayThread;
    if (g_netWatchThread) waitThreads[waitCount++] = g_netWatchThread;
    if (hActiveWorker) waitThreads[waitCount++] = hActiveWorker;
    if (hDnsWorker) waitThreads[waitCount++] = hDnsWorker;

    if (waitCount > 0) {
        Wh_Log(L"Waiting for %d threads to exit...", waitCount);
        DWORD waitResult = WaitForMultipleObjects(waitCount, waitThreads, TRUE, 5000);
        if (waitResult == WAIT_TIMEOUT) {
            Wh_Log(L"Threads did not exit in time; ExitProcess will clean up");
        }
    }

    // Step 4: cleanup handles
    if (g_trayThread) {
        CloseHandle(g_trayThread);
        g_trayThread = nullptr;
    }
    if (g_netWatchThread) {
        CloseHandle(g_netWatchThread);
        g_netWatchThread = nullptr;
    }
    if (g_shutdownEvent) {
        CloseHandle(g_shutdownEvent);
        g_shutdownEvent = nullptr;
    }
    if (hActiveWorker) {
        CloseHandle(hActiveWorker);
    }
    if (hDnsWorker) {
        CloseHandle(hDnsWorker);
    }

    // Step 5: destroy current icon safely
    HICON oldIcon = (HICON)InterlockedExchangePointer((PVOID*)&g_currentIcon, nullptr);
    if (oldIcon) {
        DestroyIcon(oldIcon);
    }

    if (g_hWindHawkBmp)  { DeleteObject(g_hWindHawkBmp);  g_hWindHawkBmp  = nullptr; }
    if (g_hWindHawkIcon) { DestroyIcon(g_hWindHawkIcon);  g_hWindHawkIcon = nullptr; }

    WSACleanup();
    Wh_Log(L"Net-Toggle Mod Uninit complete");
}

////////////////////////////////////////////////////////////////////////////////
// Windhawk tool mod implementation for mods which don't need to inject to other
// processes or hook other functions. Context:
// https://github.com/ramensoftware/windhawk/wiki/Mods-as-tools:-Running-mods-in-a-dedicated-process
//
// The mod will load and run in a dedicated windhawk.exe process.
//
// Paste the code below as part of the mod code, and use these callbacks:
// * WhTool_ModInit
// * WhTool_ModSettingsChanged
// * WhTool_ModUninit
//
// Currently, other callbacks are not supported.

bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;

void WINAPI EntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

BOOL Wh_ModInit() {
    DWORD sessionId;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &sessionId) &&
        sessionId == 0) {
        return FALSE;
    }

    bool isExcluded = false;
    bool isToolModProcess = false;
    bool isCurrentToolModProcess = false;
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);
    if (!argv) {
        Wh_Log(L"CommandLineToArgvW failed");
        return FALSE;
    }

    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-service") == 0 ||
            wcscmp(argv[i], L"-service-start") == 0 ||
            wcscmp(argv[i], L"-service-stop") == 0) {
            isExcluded = true;
            break;
        }
    }

    for (int i = 1; i < argc - 1; i++) {
        if (wcscmp(argv[i], L"-tool-mod") == 0) {
            isToolModProcess = true;
            if (wcscmp(argv[i + 1], WH_MOD_ID) == 0) {
                isCurrentToolModProcess = true;
            }
            break;
        }
    }

    LocalFree(argv);

    if (isExcluded) {
        return FALSE;
    }

    if (isCurrentToolModProcess) {
        g_toolModProcessMutex =
            CreateMutex(nullptr, TRUE, L"windhawk-tool-mod_" WH_MOD_ID);
        if (!g_toolModProcessMutex) {
            Wh_Log(L"CreateMutex failed");
            ExitProcess(1);
        }

        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            Wh_Log(L"Tool mod already running (%s)", WH_MOD_ID);
            ExitProcess(1);
        }

        if (!WhTool_ModInit()) {
            ExitProcess(1);
        }

        IMAGE_DOS_HEADER* dosHeader =
            (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders =
            (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);

        DWORD entryPointRVA = ntHeaders->OptionalHeader.AddressOfEntryPoint;
        void* entryPoint = (BYTE*)dosHeader + entryPointRVA;

        Wh_SetFunctionHook(entryPoint, (void*)EntryPoint_Hook, nullptr);
        return TRUE;
    }

    if (isToolModProcess) {
        return FALSE;
    }

    g_isToolModProcessLauncher = true;
    return TRUE;
}

void Wh_ModAfterInit() {
    if (!g_isToolModProcessLauncher) {
        return;
    }

    WCHAR currentProcessPath[MAX_PATH];
    switch (GetModuleFileName(nullptr, currentProcessPath,
                              ARRAYSIZE(currentProcessPath))) {
        case 0:
        case ARRAYSIZE(currentProcessPath):
            Wh_Log(L"GetModuleFileName failed");
            return;
    }

    WCHAR
    commandLine[MAX_PATH + 2 +
                (sizeof(L" -tool-mod \"" WH_MOD_ID "\"") / sizeof(WCHAR)) - 1];
    swprintf_s(commandLine, L"\"%s\" -tool-mod \"%s\"", currentProcessPath,
               WH_MOD_ID);

    HMODULE kernelModule = GetModuleHandle(L"kernelbase.dll");
    if (!kernelModule) {
        kernelModule = GetModuleHandle(L"kernel32.dll");
        if (!kernelModule) {
            Wh_Log(L"No kernelbase.dll/kernel32.dll");
            return;
        }
    }

    using CreateProcessInternalW_t = BOOL(WINAPI*)(
        HANDLE hUserToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
        LPSECURITY_ATTRIBUTES lpProcessAttributes,
        LPSECURITY_ATTRIBUTES lpThreadAttributes, WINBOOL bInheritHandles,
        DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory,
        LPSTARTUPINFOW lpStartupInfo,
        LPPROCESS_INFORMATION lpProcessInformation,
        PHANDLE hRestrictedUserToken);
    CreateProcessInternalW_t pCreateProcessInternalW =
        (CreateProcessInternalW_t)GetProcAddress(kernelModule,
                                                 "CreateProcessInternalW");
    if (!pCreateProcessInternalW) {
        Wh_Log(L"No CreateProcessInternalW");
        return;
    }

    STARTUPINFO si{
        .cb = sizeof(STARTUPINFO),
        .dwFlags = STARTF_FORCEOFFFEEDBACK,
    };
    PROCESS_INFORMATION pi;
    if (!pCreateProcessInternalW(nullptr, currentProcessPath, commandLine,
                                 nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS,
                                 nullptr, nullptr, &si, &pi, nullptr)) {
        Wh_Log(L"CreateProcess failed");
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void Wh_ModSettingsChanged() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModUninit();
    ExitProcess(0);
}
