# 1-Self-study — Lộ trình học engine (full clone GZDoom, drop WAD chơi được)

Mục tiêu của bạn: học **game/engine** đồng thời học **kiến trúc máy tính + OS + build system** bằng cách đọc GZDoom và tự viết một dự án **full clone** theo hướng:

- Thả `*.wad` / `*.pk3` vào là chạy và chơi được như engine gốc (tương thích hành vi + nội dung + modding ở mức cao).
- Renderer theo hướng engine gốc (OpenGL và/hoặc Vulkan, cuối cùng phải đạt tương đương).
- Bạn **tự tay code từng file** trong thư mục tự học này.

- Tất cả bài tập/ghi chú/code bạn tự viết đặt trong thư mục này.
- Repo gốc (GZDoom) dùng như “sách giáo khoa”: đọc, debug, đo đạc, và đối chiếu hành vi.

> Cảnh báo phạm vi (quan trọng): GZDoom là kết quả của **hàng chục năm** phát triển, có lượng tính năng/compat/modding rất lớn.
> Ở nhịp **2 giờ/ngày**, “full clone” là mục tiêu **nhiều năm**. Lộ trình dưới đây vẫn chia ra mốc “chạy được WAD sớm”, rồi tăng mức tương thích đến khi đạt “engine gốc”.

---

## 0) Bạn sẽ hoàn thành trong bao lâu? (2 giờ/ngày)

Bạn học **2 giờ/ngày** ≈ **14 giờ/tuần** ≈ **~730 giờ/năm**.

### Thực tế về “full clone”

Nếu mục tiêu là:

- Chạy tốt `DOOM.WAD`/`DOOM2.WAD`.
- Hỗ trợ hệ sinh thái mod (lumps/PK3/DECORATE/ZScript/ACS…)
- Renderer + ánh sáng/portals/effects như GZDoom.
- Savegame/demo/network/options/console/cvar… tương đương.

Thì tổng công sức thường rơi vào **5,000–15,000 giờ** (tùy mức “giống” và phạm vi platform).

Quy đổi theo 2h/ngày:

- **5,000 giờ** → ~6.8 năm
- **10,000 giờ** → ~13.7 năm
- **15,000 giờ** → ~20.5 năm

> Bạn vẫn có thể “chơi được WAD” sớm hơn rất nhiều (6–18 tháng), nhưng để “đạt engine gốc” là chặng đường dài.

### Mốc hoàn thành theo mức tương thích

- **T0 — Tooling + debug nền tảng**: build/run/debug ổn định (2–4 tuần)
- **T1 — Chạy được DOOM1.WAD (cơ bản)**: load WAD, map, movement, render đơn giản (6–18 tháng)
- **T2 — Tương thích gameplay cao + tài nguyên đầy đủ**: đa số map/mod “phổ thông” chạy đúng (2–5 năm)
- **T3 — GZDoom-level modding + renderer parity (OpenGL/Vulkan)**: gần như engine gốc (6–15+ năm)

---

## 1) Quy tắc học để ra sản phẩm

1. **Mỗi tuần chỉ 1 chủ đề kỹ thuật chính** (render hoặc input hoặc map…), tránh nhảy lung tung.
2. **Mỗi chủ đề đều có deliverable chạy được** (demo nhỏ), không chỉ đọc.
3. **Viết log hằng ngày**: 3 dòng “Hôm nay hiểu gì / vướng gì / mai làm gì”.
4. **Không copy-paste nguyên khối** từ GZDoom. Được phép: đọc hiểu, ghi chú, rồi tự viết lại.
5. **Debug là một phần của học**: đặt breakpoint, xem call stack, xem data structures, đo thời gian.

Quy tắc “full clone” để không lạc đường:

6. **Luôn bám tương thích trước, tối ưu sau**: ưu tiên đúng hành vi (compat) rồi mới tối ưu.
7. **Mọi thay đổi phải có “test WAD”**: mỗi milestone gắn với 1–3 WAD/map cố định để kiểm chứng.
8. **Không tự phát minh format/logic khi mục tiêu là compat**: càng về sau càng phải đọc đúng lumps/flags/quirks.

---

## 2) Setup tối thiểu (tuần 1)

### 2.1 Mục tiêu tuần 1

- Build được GZDoom (để dùng làm “oracle” quan sát hành vi).
- Setup toolchain để debug:
  - Visual Studio (hoặc VS Build Tools)
  - CMake + Ninja/MSBuild
  - vcpkg (repo này đã có `vcpkg.json`)

### 2.2 Deliverable

- Bạn có thể:
  - Build thành công
  - Run binary
  - Attach debugger, đặt breakpoint vào `main`/entry point và chạy tới menu

> README gốc của repo chỉ trỏ tới wiki build (zdoom.org). Nếu bạn gặp lỗi build, hãy ghi lại log + config CMake vào logbook.

---

## 3) Lộ trình theo phase (đi từ dễ → khó)

### Phase A — Đọc codebase như một kỹ sư (tuần 2–4)

**Mục tiêu:** học cách “định vị” trong code engine lớn.

Checklist:

- Biết cách dùng tìm kiếm theo symbol (Ctrl+T), “Find All References”, call hierarchy.
- Vẽ bản đồ module (1 trang): platform, file system, config, game loop, renderer, audio.
- Chọn 5 file “xương sống” để đọc sâu (entry/game loop/config/map).

Deliverable:

- Một sơ đồ kiến trúc 1 trang (markdown/ảnh) trong thư mục này.

### Phase B — Tự viết project clone (nền tảng bắt buộc) (tuần 5–12)

**Mục tiêu:** có một executable “engine sandbox” của riêng bạn.

Bạn sẽ tự tạo một dự án CMake trong `1-Self-study/` (ví dụ `engine/` hoặc `gzclone/`, tên tùy bạn) với các module gợi ý:

- `platform/`:
  - window + message loop
  - input (keyboard/mouse)
  - time (delta time)
- `core/`:
  - logging
  - assertions
  - file I/O (đọc binary)
  - memory basics (arena hoặc new/delete trước cũng được)
- `math/`:
  - vector/matrix tối thiểu
- `render/`:
  - đi đúng hướng “engine gốc”: **OpenGL trước** (dễ bring-up), sau đó **Vulkan** (parity)

Deliverable (định nghĩa DONE cho nền tảng):

- chạy được một scene đơn giản (vẽ hình, di chuyển camera), có overlay debug (FPS, dt)
- hệ thống log + assert + crash dump tối thiểu (để debug lỗi khó về sau)
- build “clean” 1 lệnh, chạy được từ command line

### Phase C — Tài nguyên GZDoom: WAD/PK3/lumps (tuần 13–22)

**Mục tiêu:** đọc được tài nguyên theo “đúng kiểu Doom/GZDoom”, vì mục tiêu của bạn là thả WAD/PK3 vào chơi.

Checklist:

- Virtual filesystem: mount folder + WAD + PK3/zip
- Lumps: directory, namespace, overrides, search order
- Texture system cơ bản: patch/texture definitions (mức tối thiểu để hiện được tường/sàn)
- Palette/colormap (ít nhất để decode graphic lumps cổ điển)

Deliverable:

- mở được `DOOM.WAD`, liệt kê lumps, đọc được các lump quan trọng
- nạp được 1 map và in ra thống kê (vertex/line/sector/thing)

### Phase D — Map formats (Doom + Hexen) + movement/collision (tuần 23–40)

**Mục tiêu:** “đi lại được trong map”.

Checklist:

- Player movement theo Doom-ish rules (đúng step height, friction, slide)
- Collision với lines/sectors (đúng “feel” ở mức cơ bản)
- “Things” spawn đúng vị trí + flags tối thiểu
- Debug draw collision + line-of-sight (để debug AI về sau)

Deliverable:

- vào được E1M1 (hoặc MAP01) và đi lại ổn định, không xuyên tường
- có chế độ `noclip`/debug camera để kiểm tra map

### Phase E — Renderer theo hướng GZDoom (OpenGL trước) (tuần 41–78)

Bạn chọn **renderer theo engine gốc**, nên lộ trình hợp lý là:

- Bring-up OpenGL: context, swapchain, shader pipeline tối thiểu
- Draw world cơ bản: walls/flats/sprites (đúng thứ tự hiển thị cơ bản)
- Texture manager + atlasing/streaming tối thiểu
- Lighting cơ bản (không cần đẹp ngay, nhưng phải đúng logic dần)

Deliverable:

- render được E1M1/MAP01 “đi lại bắn được”, có tường/sàn/sprite
- overlay debug: draw calls, triangles, GPU time

### Phase F — Gameplay core + thinker/tick system (tuần 79–110)

Checklist:

- Tick system đúng nhịp (ticrate), thinker list, deterministic rules (càng đúng càng tốt)
- Weapons cơ bản + pickups
- AI cơ bản (chase/attack), door/lift/platform interactions
- Save/load: có thể postpone, nhưng cần thiết cho “engine gốc”

Deliverable:

- “chơi được campaign cơ bản” (ít nhất Doom 1 episode 1) ở mức chấp nhận được
- có hệ thống config + console command tối thiểu để debug

---

## 4) Roadmap để đạt “thả WAD/PK3 chạy như GZDoom” (multi-year)

Phần này là các phase dài hạn sau khi bạn đã “chơi được Doom cơ bản”.

### Phase G — Audio, UI/menu, input hoàn chỉnh, config/cvar/console (6–12 tháng)

- Audio mixer + sound effects + music (MIDI/OGG… tùy thứ tự)
- Menu/UI cơ bản, keybinds, options
- Console, CVAR system, config files (để parity dần)

### Phase H — Scripting + modding nền (1–3 năm)

Đây là “trái tim” khiến GZDoom khác xa engine Doom cổ điển.

- DECORATE/actor defs (hoặc đi thẳng ZScript tùy chiến lược)
- ACS (scripts trong map)
- MAPINFO/KEYCONF/animdefs… (tùy mức compat)

### Phase I — Renderer parity (OpenGL nâng cao + Vulkan) (2–6 năm)

- Dynamic lights, shadowmaps/portal rendering (tùy lộ trình)
- Materials, post-processing, scene buffers
- Vulkan backend đạt parity feature set với OpenGL path

### Phase J — Savegame/demo/netplay/recording (2–5 năm)

- Savegame format + backward compat (rất khó nếu muốn “như engine gốc”)
- Demo recording/playback determinism
- Networking/netcode parity (phức tạp)

### Phase K — Edge cases/compat flags + “độ đúng” như GZDoom (liên tục)

- Hundreds of compatibility quirks
- Performance tuning, threading
- Tooling: regression tests với bộ WAD lớn

---

## 5) Gợi ý học kèm kiến trúc máy tính/OS (xuyên suốt)

Mỗi tuần chọn 1 “trục học OS/architecture” gắn với thứ bạn đang code:

- Game loop/time → clock, timer resolution, scheduling, vsync
- Input → message queue, event processing, polling vs event-driven
- File I/O → buffering, paging, mmap (đọc thêm), cache locality
- Renderer software → cache, branch prediction, SIMD (đọc thêm)
- Multithreading (sau M1) → data race, lock, job system

Deliverable chung:

- Mỗi chủ đề viết 5–10 dòng ghi chú “OS/arch đã học” vào logbook.

---

## 6) Cách đọc GZDoom hiệu quả (không bị ngợp)

- Bắt đầu từ “điểm vào” và “vòng lặp chính”: tìm nơi khởi tạo game, load config, tick/update.
- Khi đọc, luôn trả lời 3 câu:
  1. Dữ liệu vào là gì?
  2. Biến đổi thế nào?
  3. Dữ liệu ra/side-effects là gì?
- Dùng debugger như kính hiển vi:
  - break ở nơi bạn tò mò
  - step over/into
  - xem call stack + watch variables

Tip: mỗi lần đọc chỉ lấy **1 đường đi** (happy path) trước, rồi mới quay lại edge cases.

---

## 7) Checklist theo tuần (mẫu 2h/ngày)

Mỗi tuần (14h/tuần):

- 4h đọc + debug theo “một đường đi” (happy path)
- 8h tự code + chạy demo + sửa bug
- 2h tổng kết + viết note + chuẩn hóa build

Mẫu tổng kết cuối tuần (copy vào log):

- Đã làm được:
- Chưa làm được (vì sao):
- Tuần sau:

---

## 8) Tiêu chí “đủ tốt” để chuyển phase

Bạn chỉ chuyển phase khi:

- Build 1 lệnh ra được executable
- Có demo chạy ổn định
- Có ghi chú ngắn giải thích kiến trúc hiện tại
- Biết cách debug lỗi crash cơ bản (stack trace, assert)

---

## 9) Đề xuất cấu trúc thư mục trong 1-Self-study (bạn tự tạo dần)

- `notes/` ghi chú theo chủ đề
- `logbook.md` nhật ký hằng ngày
- `gdoom-mini/` dự án clone của bạn
- `diagrams/` sơ đồ kiến trúc

---

## 10) “Định nghĩa DONE” cho mục tiêu full clone

Bạn đạt mục tiêu khi (tối thiểu):

- Có thể chạy một tập WAD/PK3 phổ biến (IWAD + mod) với hành vi tương đương GZDoom trong phạm vi bạn đặt ra
- Renderer OpenGL và Vulkan đều hoạt động ổn định (nếu bạn chọn parity cả hai)
- Hệ thống modding chính yếu (ZScript/DECORATE/ACS… theo mục tiêu) chạy được với compatibility chấp nhận
- Có bộ regression WAD riêng để kiểm chứng mỗi lần thay đổi

Nếu bạn muốn, bước tiếp theo mình có thể làm ngay là thêm một mục “Bộ WAD kiểm chứng theo milestone” (E1M1/MAP01 + một vài WAD test) để bạn có checklist kiểm tra mỗi phase.
