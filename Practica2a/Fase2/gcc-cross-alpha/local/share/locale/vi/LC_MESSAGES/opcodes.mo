??    ?      ?  ?   l	      ?     ?  L   ?  K   ?  ?   $  u   ?  ?   X  ?   ?  k   ?  }   ?  [   u  ?   ?     _  9   s  3   ?  4   ?  (        ?     L     \     h     v     ?  	   ?     ?  	   ?     ?     ?            (   :     c     y     ?     ?     ?     ?     
     '  &   9  *   `     ?  
   ?  D   ?  C   ?  +   7  &   c  ,   ?     ?  :   ?  1     9   @  6   z     ?  "   ?  !   ?       )   (     R     p  %   ?  #   ?  +   ?  +   ?  1   $  1   V  %   ?  +   ?  1   ?  1     %   >  $   d  /   ?     ?     ?     ?       .     +   I     u     ?     ?  #   ?  7   ?  !   !  !   C  5   e  "   ?  +   ?     ?  0        6     F  "   a     ?     ?  )   ?     ?          %     @  %   S  &   y     ?     ?     ?  !   ?  ;   ?     2  +   P  /   |     ?     ?     ?     ?          *     E  !   `  !   ?     ?  &   ?  2   ?  2      2   P   0   ?   ,   ?      ?   )   ?      %!     D!     a!  5   {!  $   ?!  -   ?!  ;   "  $   @"  /   e"  	   ?"     ?"     ?"     ?"     ?"     ?"     ?"     #      #     >#     W#  ?  j#     %  d   %  c   y%  ?   ?%  ?   ?&  ?   '  ?   ?'  e   g(  n   ?(  m   <)  ?   ?)     N*  F   b*  ;   ?*  ?   ?*  A   %+     g+     +  	   ?+     ?+  )   ?+  )   ?+     
,  *   ,     B,  *   V,     ?,  $   ?,     ?,  >   ?,     
-  ,   '-  )   T-  ,   ~-     ?-  &   ?-  '   ?-     .  :   -.  6   h.     ?.  	   ?.  n   ?.  p   -/  K   ?/  F   ?/  J   10     |0  @   ?0  8   ?0  @   1  H   L1      ?1  &   ?1  ;   ?1  ,   2  9   F2  A   ?2     ?2  )   ?2  4   3  E   93  D   3  J   ?3  A   4  9   Q4  ?   ?4  K   ?4  B   5  <   Z5  =   ?5  C   ?5     6     56     Q6  $   q6  K   ?6  J   ?6  (   -7  '   V7  #   ~7  ,   ?7  }   ?7  5   M8  &   ?8  K   ?8  .   ?8  7   %9  0   ]9  G   ?9     ?9  *   ?9  3   !:  0   U:  /   ?:  M   ?:  .   ;  *   3;  ,   ^;  &   ?;  9   ?;  <   ?;  %   )<  #   O<  $   s<  8   ?<  M   ?<  ,   =  U   L=  Y   ?=     ?=     >     &>  /   :>  .   j>  .   ?>  .   ?>  3   ?>  3   +?  <   _?  I   ??  L   ??  L   3@  L   ?@  J   ?@  P   A  "   iA  <   ?A  b   ?A  %   ,B  2   RB  Q   ?B  2   ?B  C   
C  S   NC  1   ?C  I   ?C     D  
   3D     >D     QD     eD  #   xD  )   ?D  :   ?D  '   E      )E  "   JE     ?          y   ?       @   B   >      z   9   K         ?           /   _   ?   j   ?                k   &   x   ?   v   ?       H   U   q   h   ?   )   7   G       .               ?   0   X   *       6   F   `   s           |   ~       b       ?      T   ;   #   i                  t      !   \   W          4   }   8       ?   d       R   ]   f      
   a   ?   N      m   ?       5               r       ,       M   ?              {          ?   ?      ?   "   Q   ?       '               	   O   ?   l   V   w   P   3   u              n   ?   D   p   2   ?       L       =                 (                   ?       o   E   :      %   Z   c   g   C   1              $   e   +   Y   [       I          -       J           A              S   ^   ?   <          
 
  For the options above, The following values are supported for "ARCH":
    
  For the options above, the following values are supported for "ABI":
    
  cp0-names=ARCH           Print CP0 register names according to
                           specified architecture.
                           Default: based on binary being disassembled.
 
  fpr-names=ABI            Print FPR names according to specified ABI.
                           Default: numeric.
 
  gpr-names=ABI            Print GPR names according to  specified ABI.
                           Default: based on binary being disassembled.
 
  hwr-names=ARCH           Print HWR names according to specified 
			   architecture.
                           Default: based on binary being disassembled.
 
  reg-names=ABI            Print GPR and FPR names according to
                           specified ABI.
 
  reg-names=ARCH           Print CP0 register and HWR names according to
                           specified architecture.
 
The following ARM specific disassembler options are supported for use with
the -M switch:
 
The following MIPS specific disassembler options are supported for use
with the -M switch (multiple options should be separated by commas):
 # <dis error: %08x> # internal disassembler error, unrecognised modifier (%c) # internal error, incomplete extension sequence (+) # internal error, undefined extension sequence (+%c) # internal error, undefined modifier(%c) $<undefined> %02x		*unknown* %s: Error:  %s: Warning:  (DP) offset out of range. (SP) offset out of range. (unknown) *unknown operands type: %d* *unknown* 21-bit offset out of range <function code %d> <illegal precision> <internal disassembler error> <internal error in opcode table: %s %s>
 <unknown register %d> Address 0x%s is out of bounds.
 Attempt to find bit index of 0 Bad case %d (%s) in %s:%d
 Bad immediate expression Bad register in postincrement Bad register in preincrement Bad register name Byte address required. - must be even. Don't know how to specify # dependency %s
 Don't understand 0x%x 
 Hmmmm 0x%x IC note %d for opcode %s (IC:%s) conflicts with resource %s note %d
 IC note %d in opcode %s (IC:%s) conflicts with resource %s note %d
 IC:%s [%s] has no terminals or sub-classes
 IC:%s has no terminals or sub-classes
 Illegal limm reference in last instruction!
 Internal disassembler error Internal error:  bad sparc-opcode.h: "%s", %#.8lx, %#.8lx
 Internal error: bad sparc-opcode.h: "%s" == "%s"
 Internal error: bad sparc-opcode.h: "%s", %#.8lx, %#.8lx
 Internal: Non-debugged code (test-case missing): %s:%d Label conflicts with `Rx' Label conflicts with register name No relocation for small immediate Operand is not a symbol Small operand was not an immediate number Syntax error: No trailing ')' Unknown error %d
 Unrecognised disassembler option: %s
 Unrecognised register name set: %s
 Unrecognized field %d while building insn.
 Unrecognized field %d while decoding insn.
 Unrecognized field %d while getting int operand.
 Unrecognized field %d while getting vma operand.
 Unrecognized field %d while parsing.
 Unrecognized field %d while printing insn.
 Unrecognized field %d while setting int operand.
 Unrecognized field %d while setting vma operand.
 W keyword invalid in FR operand slot. Warning: rsrc %s (%s) has no chks%s
 attempt to set y bit when using + or - modifier bad instruction `%.50s' bad instruction `%.50s...' branch operand unaligned branch to odd offset branch value not in range and to an odd offset branch value not in range and to odd offset branch value out of range can't cope with insert %d
 can't find %s for reading
 can't find ia64-ic.tbl for reading
 cgen_parse_address returned a symbol. Literal required. class %s is defined but not used
 displacement value is not aligned displacement value is not in range and is not aligned displacement value is out of range don't know how to specify %% dependency %s
 ignoring invalid mfcr mask ignoring least significant bits in branch offset illegal bitmask illegal use of parentheses immediate value cannot be register immediate value is out of range immediate value must be even immediate value not in range and not even immediate value out of range index register in load range invalid conditional option invalid mask field invalid register for stack adjustment invalid register operand when updating jump hint unaligned junk at end of line missing `)' missing mnemonic in syntax string most recent format '%s'
appears more restrictive than '%s'
 multiple note %s not handled
 no insns mapped directly to terminal IC %s
 no insns mapped directly to terminal IC %s [%s] offset greater than 124 offset greater than 248 offset greater than 62 offset not a multiple of 16 offset not a multiple of 2 offset not a multiple of 4 offset not a multiple of 8 offset not between -2048 and 2047 offset not between -8192 and 8191 offset(IP) is not a valid form opcode %s has no class (ops %d %d %d)
 operand out of range (%ld not between %ld and %ld) operand out of range (%ld not between %ld and %lu) operand out of range (%lu not between %lu and %lu) operand out of range (%lu not between 0 and %lu) operand out of range (not between 1 and 255) overlapping field %s->%s
 overwriting note %d with note %d (IC:%s)
 parse_addr16: invalid opindex. register number must be even rsrc %s (%s) has no regs
 source and target register operands must be different source register operand must be even syntax error (expected char `%c', found `%c') syntax error (expected char `%c', found end of instruction) target register operand must be even unable to change directory to "%s", errno = %s
 undefined unknown unknown	0x%02x unknown	0x%04lx unknown	0x%04x unknown constraint `%c' unknown operand shift: %x
 unknown pop reg: %d
 unrecognized form of instruction unrecognized instruction value out of range Project-Id-Version: opcodes-2.15.96
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2005-03-05 20:32+1030
PO-Revision-Date: 2006-04-05 15:14+0930
Last-Translator: Clytie Siddall <clytie@riverland.net.au>
Language-Team: Vietnamese <gnomevi-list@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=utf-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=1; plural=0
X-Generator: LocFactoryEditor 1.6b36
 
 
  Với những tùy chọn ở trên, hỗ trợ những giá trị theo đây cho « ARCH »:
    
  Với những tùy chọn ở trên, hỗ trợ những giá trị theo đây cho « ABI »:
    
  cp0-names=ARCH           In ra các _tên CP0_ theo kiến trức được ghi rõ
                           Mặc định: trên cơ sở mã nhi phân đang bị rã.
 
  fpr-names=ABI            In ra các _tên FPR_ theo ABI được ghi rõ..
                           Mặc định: dạng số
 
  gpr-names=ABI            In ra các _tên GPR_ theo ABI được ghi rõ.
                           Mặc định: trên cơ sở mã nhi phân đang bị rã
 
  hwr-names=ARCH           In ra các _tên HWR_ theo kiến trức 			 được ghi rõ.
                           Mặc định: trên cơ sở mã nhi phân đang bị rã.
 
  reg-names=ABI            In ra các _tên_ cả hai loại GPR và FPR theo ABI được ghi rõ.
 
  reg-names=ARCH           In ra các _tên_ HWR và thanh ghi CP0 theo
						kiến trức đươc ghi rõ.
 
Hỗ trợ những tùy chọn rã đặc trưng cho ARM theo đây để sử dụng với đối số -M:
 
Hỗ trợ sử dụng những tùy chọn rã đặc trưng cho MIPS theo đây
với đối số -M (hãy phân cách nhiều tùy chọn bằng dấu phẩy):
 # <lỗi rã: %08x> # lỗi rã nội bộ, không chấp nhận điều sửa đổi (%c) # lỗi nội bộ, dãy mở rộng chưa hoàn thành (+) # lỗi nội bộ, chưa định nghĩa dãy mở rộng (+%c) # lỗi nội bộ, chưa định nghĩa điều sửa đổi(%c) $<chưa định nghĩa> %02x		 • không rõ • %s: Lỗi %s: Cảnh báo :  (DP) hiệu số ở ngoại phạm vị. (SP) hiệu số ở ngoại phạm vị. (không rõ) • không biết kiểu tác tử: %d •  • không rõ • hiệu số 21-bit ở ngoại phạm vị <mã hàm %d> <không cho phép độ chính xác> <lỗi rã nội bộ> <lỗi nội bộ trong bảng opcode (mã thi hành): %s %s>
 <không biết thanh ghi %d> Địa chỉ 0x%s ở ngoại phạm vị. 
 Cố tìm ra chỉ mục bit của số 0 Chữ hoa/thường sai %d (%s) trong %s:%d
 Biểu thức trực tiếp sai Thanh ghi sai trong hậu lượng gia Thanh ghi sai trong tiền lượng gia Tên thanh ghi sai Cần đến địa chỉ byte — phải là số chẵn. Không biết cách ghi rõ # dạng phụ thuộc %s
 Không hiểu 0x%x 
 Ừm 0x%x Chú thích IC %d cho opcode (mã thi hành) %s (IC:%s) thì xung đột với tài nguyên %s chú thích %d
 Chú thích IC %d trong opcode (mã thi hành) %s (IC:%s) thì xung đột với tài nguyên %s chú thích %d
 IC:%s [%s] không có điều mở rộng hoàn thành hay hạng con nào
 IC:%s không có điều mở rộng hoàn thành hay hạng con nào
 Không cho phép tham chiếu kiểu limm trong câu lệnh cuối cùng.
 lỗi rã nội bộ Lỗi nội bộ : sparc-opcode.h sai: « %s », %#.8lx, %#.8lx
 Lỗi nội bộ : sparc-opcode.h sai: « %s » == "%s"
 Lỗi nội bộ : sparc-opcode.h sai: « %s », %#.8lx, %#.8lx
 Nội bộ : chưa gỡ lỗi mã (thiếu trường hợp thử): %s:%d Nhãn xung đột với « Rx » Nhãn xung đột với tên thanh ghi Không có điều bố trí lại số nhỏ trực tiếp Tác tử không phải là một ký hiệu Tác tử nhỏ không phải đã là số trực tiếp Lỗi cú pháp: không có dấu ngoặc đóng « ) » đi theo Không biết lỗi %d
 Không chấp nhận tùy chọn rã: %s
 Không chấp nhận tập hợp tên thanh ghi: %s
 Không chấp nhận trường %d trong khi xây dựng câu lệnh.
 Không chấp nhận trường %d trong khi giải mã câu lệnh.
 Không chấp nhận trường %d trong khi lấy tác tử số nguyên.
 Không chấp nhận trường %d trong khi lấy tác tử vma.
 Không chấp nhận trường %d trong khi phân tách.
 Không chấp nhận trường %d trong khi in ra câu lệnh.
 Không chấp nhận trường %d trong khi đặt tác tử số nguyên.
 Không chấp nhận trường %d trong khi đặt tác tử vma.
 Tử khóa W không hợp lệ trong vị trí tác tử FR. Cảnh báo : tài nguyên %s (%s) không có cản trở %s
 cố lập « bit y » khi sử dụng điều sửa đổi + hay - câu lệnh sai « %.50s » câu lệnh sai « %.50s » chưa canh lề tác tử cành nhánh đối với hiệu số lẻ giá trị nhánh ở ngoại phạm vị và đối với hiệu số lẻ giá trị cành ở ngoại phạm vị và đối với hiệu số lẻ giá trị cành ở ngoại phạm vị không thể xử lý điều chèn %d
 không tìm thấy %s để đọc
 không tìm thấy ia64-ic.tbl để đọc
 cgen_parse_address (địa chỉ phân tách cgen) đã trả gởi một ký hiệu: còn cần đến điều nghĩa chữ. đã định nghĩa còn chưa sử dụng hạng %s
 chưa canh lề giá trị di chuyển giá trị di chuyển ở ngoại phạm vị và chưa được canh lề giá trị di chuyển ở ngoại phạm vị không biết cách ghi rõ %% dạng phụ thuộc %s
 đang bỏ qua mặt nạ mfcr không hợp lệ đang bỏ qua các bit trọng đai ít nhất trong hiệu số cành không cho phép mặt nặ bit không cho phép cách sử dụng ngoặc giá trị trực tiếp không thể là thanh ghi giá trị trực tiếp ở ngoại phạm vị giá trị trực tiếp phải là số chẵn giá trị trực tiếp ở ngoạị phạm vị và không là số chẵn giá trị trực tiếp ở ngoại pham vị thanh ghi cơ số trong phạm vị tải tùy chọn điều kiện không hợp lệ trường mặt nạ không hợp lệ thanh ghi không hợp lệ để điều chỉnh đống gặp tác tử thanh ghi không hợp lệ khi cập nhật chưa canh lề lời gợi ý nhảy gặp rác tại kết thức dòng thiếu dấu ngoặc đóng « ) » thiếu điều giúp trí nhớ trong chuỗi cú pháp dạng thức gần đây nhất « %s »
có vẻ hạn hẹp hơn « %s »
 không xử lý được đa chú thích %s
 không ảnh xạ câu lệnh nào trực tiếp vào IC mở rộng hoàn thành %s
 không ảnh xạ câu lệnh nào trực tiếp vào IC mở rộng hoàn thành %s [%s] hiệu số hơn 124 hiệu số hơn 248 hiệu số hơn 62 hiệu số không phải là bội số cho 16 hiệu số không phải là bội số cho 2 hiệu số không phải là bội số cho 4 hiệu số không phải là bội số cho 8 hiệu số không phải ở giữa -2048 và 2047 hiệu số không phải ở giữa -8192 và 8191 offset(IP) (hiệu số) không phải là dạng hợp lệ opcode (mã thi hành) %s không có hạng (những tác tử %d %d %d)
 tác tử ở ngoại phạm vị (%ld không phải ở giữa %ld và %ld) tác tử ở ngoại phạm vị (%ld không phải ở giữa %ld và %lu) tác tử ở ngoại phạm vị (%lu không phải ở giữa %lu và %lu) tác tử ở ngoại phạm vị (%lu không phải ở giữa 0 và %lu) tác tử ở ngoại phạm vị (không phải ở giữa số 1 và số 255) trường chồng lấp %s → %s
 đang ghi đè chú thích %d bằng chú thích %d (IC:%s)
 parse_addr16: (địa chỉ phân tách) opindex (chỉ mục kiểu tác tử) không hợp lệ. số thanh ghi phải là số chẵn Tài nguyên %s (%s) không có tàì nguyên con
 tác tử thanh ghi kiểu cả nguồn lẫn đích đều phải là khác nhau tác tử thanh ghi nguồn phải là số chẵn gặp lỗi cú pháp (ngờ ký tự « %c », còn tìm « %c ») gặp lỗi cú pháp (ngờ ký tự « %c », còn tìm kết thức câu lệnh) tác tử thanh ghi đích phải là số chẵn không thể chuyển đổi thư mục thành « %s », số lỗi = %s
 chưa định nghĩa không rõ 	0x%02x không rõ 	0x%04lx không rõ 	0x%04x không rõ không biết ràng buộc « %c » không biết cách dịch tác tử: %x
 không biết thanh ghi trong câu lệnh pop đống: %d
 không chấp nhận dạng câu lệnh không chấp nhận câu lệnh giá trị ở ngoại phạm vị 