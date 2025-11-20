 --- GIAI ĐOẠN KHỞI TẠO ---
Start((Bắt đầu)) --> LoadData[Load dữ liệu từ CSV\nMovies, Customers, Staff, Showtimes]
LoadData --> MainLoop{Menu Chính}

 --- NHÁNH 1: ĐĂNG KÝ ---
MainLoop -->|3. Đăng ký mới| InputReg[Nhập Tên, Email, SĐT]
InputReg --> SaveReg[Tạo ID mới & Lưu vào CSV]
SaveReg --> MainLoop

 --- NHÁNH 2: KHÁCH HÀNG ---
MainLoop -->|1. Khách hàng| LoginC[Chọn tài khoản Khách]
Login -- Thành công --> MenuC{Menu Khách hàng}
Login -- Hủy --> MainLoop

Chức năng Đặt vé
Menu -->|1. Đặt vé| ViewShow[Xem danh sách Suất chiếu]
ViewShow --> SelectShow[Chọn Suất chiếu]
SelectShow --> ShowMap[Hiển thị sơ đồ ghế]
ShowMap --> SelectSeat[Nhập vị trí ghế]
SelectSeat --> CheckSeat{Ghế trống?}
CheckSeat -- Không --> SelectSeat
CheckSeat -- Có --> BookAction[Tạo vé & Lưu trạng thái ghế]
BookAction --> MenuC

Chức năng Hủy & Lịch sử
Menu -->|2. Hủy vé| ViewHist[Xem lịch sử đặt vé]
ViewHist --> SelectCancel[Nhập ID vé cần hủy]
SelectCancel --> UpdateCancel[Cập nhật trạng thái Vé & Ghế]
UpdateCancel --> MenuC

Menu -->|3. Xem lịch sử| ShowHist[In danh sách vé]
ShowHist --> Menu

Menu -->|0. Đăng xuất| MainLoop

--- NHÁNH 3: NHÂN VIÊN ---
MainLoop -->|2. Nhân viên| Login[Chọn tài khoản Staff]
Login -- Thành công --> Menu{Menu Nhân viên}
Login -- Hủy --> MainLoop

Quản lý suất chiếu
Menu -->|1. Thêm suất| InputShow[Chọn Phim, nhập Giờ, Giá]
InputShow --> SaveShow[Lưu suất chiếu mới vào CSV]
SaveShow --> Menu

Menu -->|2. Xóa suất| ViewAllShows[Xem DS Suất chiếu]
ViewAllShows --> SelectDel[Nhập ID cần xóa]
SelectDel --> DelAction[Xóa khỏi Vector & Ghi lại CSV]
DelAction --> Menu

Menu -->|3. Sửa suất| SelectEdit[Nhập ID cần sửa]
SelectEdit --> InputEdit[Nhập Giờ/Giá mới]
InputEdit --> UpdateShow[Cập nhật & Lưu CSV]
UpdateShow --> Menu

Menu -->|0. Đăng xuất| MainLoop

--- KẾT THÚC ---
MainLoop -->|0. Thoát| End((Kết thúc))
