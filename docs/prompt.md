You are the lead engineer responsible for implementing and validating a production-quality Linux desktop application called ClipSnap.

Build the application in this repository. Do not stop at a design document, scaffold, pseudocode, or mocked demo.

Your responsibility is to write the code, build it, run available tests, fix failures, and document exactly what works and what remains unverified.

IMPORTANT:
Do not claim universal Linux compatibility or complete functionality without evidence. A headless CI test does not prove desktop integration works. Implement capability detection and graceful degradation instead of pretending unsupported features work.

────────────────────────────────────────
1. PRODUCT REQUIREMENTS
────────────────────────────────────────

ClipSnap combines region screenshots and searchable clipboard history.

Primary action A: Alt+Shift+S
- Activate region screenshot capture.
- Let the user select a rectangular area.
- Enter confirms; Escape cancels, where our own selector is used.
- Copy the resulting image to the clipboard.
- Add it to persistent history exactly once.
- Show a notification with available edit/save actions.
- Never silently capture the whole screen when region capture was requested.
- Desktop-native selection UI is acceptable when required by the supported backend.
- If only an authorized full screenshot is available, offer explicit cropping as a clearly explained fallback; do not represent it as native region capture.

Primary action B: Alt+H
- Open or toggle the clipboard history window.
- Show text previews and image thumbnails.
- Provide search and filters: All, Text, Images, Pinned.
- Support arrow-key navigation.
- Enter restores the selected item to the clipboard and closes the window.
- Escape closes without changing clipboard contents.
- Selecting an item must not create a duplicate history entry.
- Do not implement automatic paste/input injection in version 1.

Shortcuts:
- Defaults are preferences, not guaranteed reservations.
- Allow users to change them.
- Detect conflicts or unsuccessful registration where possible.
- When global shortcut APIs are unavailable, provide desktop binding instructions for our CLI commands.

History:
- Capture supported text and raster-image content while monitoring is running.
- Preserve exact text, including whitespace.
- Support pinning, individual deletion, clearing unpinned history, and clearing all history.
- Show timestamps and approximate item sizes.
- History monitoring must be explicitly enabled during onboarding.
- Explain that older clipboard contents cannot be reconstructed.
- Do not claim support for arbitrary clipboard formats unless implemented and tested.

Additional version 1 features:
- Screenshot editor: crop, arrows, rectangles, text, undo/redo.
- Solid opaque redaction, flattened into exported images.
- Save/export to PNG.
- Pause/resume clipboard monitoring with a visible status.
- Configurable history retention and storage limits.
- Settings and compatibility diagnostics.
- Optional per-user autostart, disabled until the user enables it.

Out of scope:
- Cloud sync.
- Screen recording.
- Scrolling screenshots.
- Automatic paste.
- OCR unless all required core functionality is complete.
- Undocumented security bypasses.

────────────────────────────────────────
2. TECHNOLOGY AND STRUCTURE
────────────────────────────────────────

Use:
- C++20.
- Qt 6.
- Qt Quick/QML for the application UI.
- CMake and Ninja where available.
- Qt D-Bus for desktop integration.
- SQLite for metadata and text search.
- Files for image payloads and thumbnails.
- XCB for necessary native X11 integration.
- A dedicated Wayland data-control client where supported.
- A small GNOME Shell JavaScript extension for clipboard monitoring when required.

Do not introduce Rust, Electron, or a web-server-based UI.

Before selecting APIs:
- Inspect installed Qt, compiler, desktop, display server, portal interfaces, and available dependencies.
- Consult current authoritative API documentation where necessary.
- Verify signatures and interface versions.
- Do not invent APIs, assume portal capabilities, or copy obsolete desktop-specific methods without checking them.

Organize into logical modules:
- Application/single-instance IPC.
- Capability detection.
- Screenshot backends.
- Clipboard backends.
- Shortcut backends.
- History repository.
- Settings.
- UI and screenshot editor.
- Diagnostics.
- Tests.
- Packaging.
- GNOME extension, if needed.

Backend contracts must support asynchronous results:
- Success.
- Cancellation.
- Permission denial.
- Unsupported capability.
- Backend failure.

Use explicit ownership, RAII, and clear thread boundaries.
Do not block the GUI thread on image decoding, file I/O, clipboard transfers, or D-Bus requests.
Never log clipboard payloads.

────────────────────────────────────────
3. IMPLEMENTATION WORKFLOW
────────────────────────────────────────

Start by inspecting the repository and execution environment.

Do not overwrite unrelated files or discard existing user changes.
Do not publish, push, or modify remote services.

Create a concise implementation plan and a persistent task checklist.

Then implement working vertical slices:

A. Buildable application, single-instance behavior, settings, and IPC.
B. History repository with real text/image round trips.
C. History UI with search, pinning, deletion, and clipboard restoration.
D. Working screenshot capture in the available desktop session.
E. Additional screenshot/clipboard/shortcut backends.
F. Annotation editor, privacy controls, retention, and diagnostics.
G. Packaging and final validation.

After each slice:
- Build.
- Run relevant tests.
- Fix errors.
- Update the checklist with evidence.

Do not ask me routine implementation questions.
Choose reasonable defaults and document them.
Ask only when genuinely blocked by missing permissions, required credentials, or a consequential product ambiguity.

Do not download or execute arbitrary installer scripts.
If dependencies or real desktop sessions are unavailable, document the blocker and continue with independently testable work.

────────────────────────────────────────
4. DESKTOP BACKENDS
────────────────────────────────────────

Detect capabilities, not just distribution names.

Use environment variables only as hints.
Verify available D-Bus interfaces, portal versions, Wayland globals, and actual behavior.

X11:
- Implement screenshot acquisition and our region-selection overlay.
- Implement clipboard monitoring and restoration.
- Use proper event-driven selection handling.
- Support global shortcut registration or explicit desktop command bindings.
- Handle modifier combinations, registration failure, and keyboard-map changes.
- Never busy-poll the clipboard.

Wayland screenshots:
- Prefer the supported Screenshot portal.
- Inspect the installed API and backend behavior before deciding how region capture works.
- Handle portal Request lifecycle, asynchronous responses, cancellation, permission denial, returned URIs, and cleanup correctly.
- Do not assume every backend provides the same selection UI.
- Introduce compositor-specific capture only where documented and testable.
- Do not depend on grim/slurp as a universal solution.
- Do not attempt X11 screen capture through XWayland as a substitute for native Wayland desktop capture.

Wayland clipboard:
- Prefer ext-data-control-v1 where advertised.
- Support legacy wlr-data-control as a fallback where practical.
- Manage offer/source lifetimes and asynchronous file-descriptor transfers correctly.
- Handle ownership loss, compositor disconnects, and backend restarts.
- Do not assume ordinary Qt clipboard signals provide universal background monitoring.
- Do not use a RemoteDesktop clipboard portal session solely to obtain clipboard-history access.

GNOME Wayland:
- If a supported background-monitoring API is unavailable, implement a minimal companion GNOME Shell extension.
- Forward clipboard events through a narrowly scoped per-user D-Bus interface.
- Validate sender identity and payloads.
- Keep extension responsibilities minimal.
- Declare only GNOME Shell versions actually tested or verified.
- Without the extension, expose limited-history mode rather than claiming complete monitoring.
- Do not install or enable an extension without user consent.

Global shortcuts:
- Use the GlobalShortcuts portal where available.
- Handle user approval, rejected bindings, session lifetime, and changed bindings.
- Use a native X11 backend on X11 where appropriate.
- Otherwise expose CLI commands and desktop-specific setup instructions.
- Never require root or raw keyboard-device access.

────────────────────────────────────────
5. CLI AND SINGLE-INSTANCE BEHAVIOR
────────────────────────────────────────

Implement:
- clipsnap capture --region
- clipsnap history
- clipsnap pause
- clipsnap resume
- clipsnap doctor
- clipsnap --version

Commands must reach the existing per-user instance.
If appropriate, launch the instance when it is not running.

Avoid duplicate clipboard watchers.
Restrict IPC access to the current user.
Validate command arguments and payloads.

Do not rely on a system tray being available.
History and settings must remain accessible through the application launcher.

────────────────────────────────────────
6. STORAGE AND PRIVACY
────────────────────────────────────────

Use XDG locations for configuration, state, and application data.

Suggested defaults:
- 500 history entries.
- Seven-day retention for unpinned items.
- 250 MB total storage budget.
- A configurable maximum payload size and image pixel count.

Pinned items are exempt from ordinary age/count eviction, but not an unlimited disk budget.
If pinned content consumes the budget, warn and stop accepting new stored entries rather than silently deleting pinned items.

Model each history item with multiple MIME representations where supported:
- Item identifier.
- Timestamps.
- Origin.
- Content hash.
- Pin state.
- Searchable text.
- Representations with MIME type and payload location.

Requirements:
- Transactional metadata updates.
- Atomic payload writes.
- Schema migrations.
- Crash recovery and orphan cleanup.
- Content deduplication with documented ordering behavior.
- Prevention of feedback loops during clipboard restoration.
- Restrictive data-directory and file permissions.
- Bounded reads and transfer timeouts.
- Bounded decoded image dimensions.
- No active HTML rendering.
- No cloud requests or telemetry by default.
- No clipboard contents in logs, crash reports, or test artifacts.

When monitoring is paused, do not persist new clipboard events or new captures into history; explicitly requested screenshots may still be copied or saved.

Respect sensitive-content hints where available.
Do not claim perfect password detection or reliable source-application attribution.
Do not claim that deleting a file guarantees forensic secure erasure.
Do not claim history is encrypted unless metadata and payload encryption are actually implemented and tested.

────────────────────────────────────────
7. DISPLAY GEOMETRY
────────────────────────────────────────

Separate:
- Logical UI coordinates.
- Output-local coordinates.
- Captured-image pixel coordinates.

Handle:
- Negative monitor origins.
- Multiple monitors.
- Mixed scaling.
- Fractional scaling where supported.
- Rotated displays.
- Monitor hotplug.
- Selection cancellation.
- UI hiding before screenshot acquisition.

For our selector:
- Show selection dimensions.
- Prevent zero-sized capture.
- Normalize drag direction.
- Clamp correctly to supported bounds.

Do not silently stretch or incorrectly crop images.
If a backend cannot support cross-monitor capture correctly, restrict it explicitly and explain why.

Create unit tests for coordinate transformations using synthetic monitor layouts.

────────────────────────────────────────
8. TESTING REQUIREMENTS
────────────────────────────────────────

Write tests alongside implementation.

Use Qt Test or another justified C++ test framework integrated with CTest.

Unit tests:
- Exact text preservation.
- MIME representation handling.
- Deduplication.
- Pinning.
- Retention and storage budgets.
- Search.
- Schema migration.
- Coordinate transformations.
- Payload validation.
- Settings validation.

Integration tests:
- Persistent history across restart.
- Text and image restore round trips.
- Correct screenshot insertion without duplicates.
- IPC and single-instance behavior.
- Cancellation and permission-denial handling.
- Missing backend behavior.
- Backend disconnection/recovery.
- Payload timeouts.
- Corrupted or missing image files.
- Failed writes and storage exhaustion.

Editor tests:
- Crop output dimensions.
- Annotation coordinates.
- Undo/redo.
- PNG export.
- Opaque redaction present in exported pixels.
- No annotation layers accidentally omitted from export.

Desktop tests, where the environment permits:
- Actual shortcut activation.
- Actual selected-region capture.
- Copy from an external application.
- Restore and paste into an external application.
- Clipboard owner exits.
- Shortcut conflicts.
- Monitoring pause/resume.
- Multi-monitor scaling.
- Coexistence with another clipboard manager.

Run:
- Debug build.
- Release build.
- CTest.
- Compiler warnings.
- AddressSanitizer and UndefinedBehaviorSanitizer where supported.

Do not hide failures, disable meaningful assertions, or replace failing behavior with mocks.
Mocks are appropriate for controlled backend-failure tests, not proof of desktop functionality.

Headless/offscreen tests must be labeled as such.
Use nested sessions or Xvfb where useful, but state their limitations.

Record every test environment with actual versions.
Classify each capability as:
- Implemented and verified.
- Implemented but not verified in a real desktop session.
- Partially supported.
- Unsupported.
- Blocked.

────────────────────────────────────────
9. PACKAGING AND DOCUMENTATION
────────────────────────────────────────

Provide:
- Reproducible build instructions.
- Dependency list and supported minimum versions.
- CMake install rules.
- Desktop entry and application icon.
- Launcher access to history/settings.
- Optional autostart configuration.
- A development launch command.
- A native package recipe for the current/reference distribution where feasible.
- LICENSE and third-party license notices.
- A compatibility matrix.
- Troubleshooting guide.
- GNOME extension installation/removal instructions if applicable.

Treat native and sandboxed packaging as separate compatibility targets.
Do not claim Flatpak support unless the packaged application and required integrations are actually validated.

The doctor command should report:
- Session type and desktop hints.
- Available and selected backends.
- Portal interfaces and relevant versions.
- Clipboard monitoring status.
- Shortcut registration status.
- Missing dependencies.
- Actionable fallback instructions.

Diagnostics must not expose clipboard contents.

────────────────────────────────────────
10. COMPLETION CRITERIA
────────────────────────────────────────

Keep working until the required features are implemented and all executable tests pass, or you encounter a genuine environmental blocker.

A compiling scaffold is not completion.
A mocked backend is not completion.
A successful screenshot on X11 is not proof of Wayland support.
A test on one desktop is not proof of universal compatibility.

Before finishing:
1. Run a clean build.
2. Run the complete test suite.
3. Perform available real-session smoke tests.
4. Check for placeholder handlers and production TODOs.
5. Verify all advertised features match actual implementation.
6. Review privacy-sensitive paths and error handling.
7. Update documentation and compatibility status.

Your final report must include:
- What was implemented.
- Exact build and test commands executed.
- Test results and failures, if any.
- Desktop/display environments actually tested.
- How to launch the app.
- How to configure both shortcuts.
- Any permissions or companion integrations required.
- Known limitations and remaining blockers.

Never say “everything works” unless the evidence supports that statement.
If desktop testing is unavailable, provide a short, precise manual test checklist and clearly identify the unverified features.

Start by inspecting this repository and the environment, then proceed to implementation.
