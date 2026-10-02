# ClipSnap 2.0 📸📋

> **Enterprise-grade, privacy-first Linux clipboard history manager & region screenshot tool with authentic Ubuntu Yaru dark styling.**

Designed specifically for modern Linux desktop environments (Wayland & X11 on GNOME, Ubuntu 22.04/24.04, Debian, and derivatives) with zero external cloud dependencies.

---

## ✨ Features

- **Responsive Card Grid UI**: Interactive, card-based showcase replacing legacy vertical lists. Cards feature syntax-highlighted code/text snippets and high-resolution thumbnail previews.
- **Click-to-Copy**: Click **anywhere** on a card or its `Copy` button to instantly prime the system clipboard for both standard paste (`Ctrl+V`) and primary selection (middle-click paste) with an immediate visual confirmation flash.
- **Region & Full Screen Snipping (`Alt+Shift+S`)**: Instant screen region capture overlay with native GNOME Mutter D-Bus integration and XDG portal fallback.
- **Search & Filtering**: Search text content, snippets, and screenshot filenames with instant filter tabs (*All Items*, *Text*, *Images*, *Pinned*).
- **History Management & Bulk Clear**:
  - **Pin items (`📌`)** to prevent eviction.
  - **Delete individual items (`🗑`)**.
  - **Delete All / Clear History** with safety options to either wipe everything or keep pinned items intact.
- **Zero-Setup System Integration**:
  - Pre-configured systemd user service (`clipsnap.service`).
  - Automatic GNOME media-key shortcut registration (`Alt+H` and `Alt+Shift+S`).
  - Seamless desktop integration with authentic Ubuntu Yaru dark palette (`#242424`, `#2D2D2D`, `#E95420`, `#AEA79F`).
- **Privacy & Performance**: Fully local SQLite storage with FTS full-text search, disk deduplication via SHA-256 hashes, and automatic retention/storage budget management. Zero telemetry.

---

## 🚀 Installation

### Option 1: Native `.deb` Package (Recommended for Ubuntu / Debian)

Install the pre-built `.deb` package with automatic dependency resolution:

```bash
sudo apt install ./dist/clipsnap_0.1.0_amd64.deb
```

*Or double-click the `.deb` file in your file manager to install via Ubuntu App Center / Software.*

#### What the `.deb` installer does automatically:
1. Installs the optimized binary to `/usr/bin/clipsnap`.
2. Registers the application icon (`clipsnap.svg`) and desktop launcher.
3. Automatically enables and starts `clipsnap.service` via `systemd --user`.
4. Configures `Alt+H` (history) and `Alt+Shift+S` (screenshot) shortcuts in GNOME settings.

---

### Option 2: Build from Source

#### Prerequisites
Install the required build dependencies on Ubuntu/Debian:
```bash
sudo apt update
sudo apt install -y \
  build-essential cmake ninja-build \
  qt6-base-dev qt6-declarative-dev qt6-quickcontrols2-dev libqt6concurrent6 \
  libsqlite3-dev
```

#### Build & Run
```bash
# Clone the repository
git clone https://github.com/clipsnap/clipsnap2.0.git
cd clipsnap2.0

# Configure & build
cmake -B build-release -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja -C build-release

# Run unit tests
ctest --test-dir build-release --output-on-failure

# Install for current user
install -m 755 build-release/src/clipsnap ~/.local/bin/clipsnap
clipsnap --setup
```

#### Build Debian Package Yourself
```bash
cd build-release
cpack -G DEB
# Generates: clipsnap_0.1.0_amd64.deb
```

---

## ⌨️ Keyboard Shortcuts & Usage

| Shortcut | Action | Description |
| :--- | :--- | :--- |
| **`Alt + H`** | **Open Clipboard History** | Opens the responsive card showcase with search bar focused |
| **`Alt + Shift + S`** | **Take Screenshot** | Starts the screen region capture and cropping overlay |
| **`Super + Shift + S`** | **Take Screenshot (Alternative)** | Standard Windows/Linux snipping shortcut |
| **`Escape`** | **Dismiss Overlay** | Closes the clipboard history or cancels the active screenshot |
| **`Enter`** | **Copy Selected Card** | Copies the highlighted card and dismisses the window |
| **`Delete`** | **Delete Item** | Deletes the currently focused card from history |

---

## 🛠️ CLI & Management Commands

ClipSnap includes built-in commands for scripting, diagnostics, and debugging:

```bash
# Open clipboard history cards
clipsnap history

# Trigger region screenshot capture
clipsnap capture

# Run comprehensive system diagnostics
clipsnap doctor

# View or clear system logs
clipsnap logs
clipsnap logs --clear

# Configure/repair desktop integration & shortcuts
clipsnap --setup

# Pause or resume clipboard monitoring
clipsnap pause
clipsnap resume

# Print version
clipsnap --version
```

---

## 🩺 System Diagnostics (`clipsnap doctor`)

ClipSnap features an internal self-diagnostic suite that verifies desktop environment compatibility, screenshot portals, clipboard monitoring status, and keyboard bindings:

```bash
clipsnap doctor
```

Example output:
```text
ClipSnap Doctor v0.1.0
======================

[Session]
  ✓ Session type: wayland
  ℹ Desktop: ubuntu:gnome

[Screenshot]
  ✓ Native GNOME Mutter capture: active (instant direct compositor screenshot)
  ✓ XDG Screenshot portal: available (fallback)

[Clipboard Monitoring]
  ✓ System Clipboard Monitoring: active (instant background sync & deduplication)

[Shortcuts]
  ✓ Global Shortcuts: configured via GNOME media-keys (Alt+H -> history, Alt+Shift+S -> capture)

[Storage & Logging]
  ✓ Data directory: ~/.local/share/clipsnap/clipsnap
  ✓ Log file: ~/.local/share/clipsnap/clipsnap/state/clipsnap.log
  ✓ SQLite available

[Overall: 0 issues found]
```

---

## ⚙️ Configuration & Storage

Settings can be customized directly in the UI (via the **⚙** button in the bottom status bar) or by editing `~/.config/clipsnap/clipsnap/clipsnap.ini`:

| Setting | Default | Description |
| :--- | :--- | :--- |
| `maxHistoryEntries` | `500` | Maximum unpinned items stored before FIFO eviction |
| `retentionDays` | `7` | Retention limit for unpinned items |
| `maxStorageMb` | `250` | Total disk budget for image payloads and database |
| `maxPayloadSizeKb` | `10240` | Maximum size per single clipboard item (10 MB) |
| `monitoringEnabled` | `true` | Background clipboard synchronization toggle |

- **History Database**: `~/.local/share/clipsnap/clipsnap/history.db`
- **Cached Thumbnails & Images**: `~/.local/share/clipsnap/clipsnap/thumbnails/`
- **Application Logs**: `~/.local/share/clipsnap/clipsnap/state/clipsnap.log`

---

## 🛡️ Privacy & Security Contract

- **100% Local**: No internet access, cloud sync, or telemetry analytics.
- **Zero Content Logging**: Clipboard text and image bytes are never written to log files.
- **Strict File Permissions**: Storage databases and image payloads are restricted to user-only read/write (`0600` / `0700`).
- **Disk Deduplication**: Content hashing prevents duplicate disk writes when copying the same item repeatedly.

---

## 🗑️ Uninstallation

To completely remove ClipSnap:

```bash
# If installed via .deb package:
sudo apt remove clipsnap

# If installed manually:
systemctl --user stop clipsnap.service
systemctl --user disable clipsnap.service
rm -f ~/.local/bin/clipsnap ~/.config/systemd/user/clipsnap.service
```

---

## 📄 License

ClipSnap is open-source software licensed under the [MIT License](LICENSE).
