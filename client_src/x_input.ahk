dll := "net_transfer.dll"
tcp := 781

; ---Functions--- ;
INIT := "net_init"
TCPT := "TCP_transfer"
EH := "NT_exc_handler"

; ---Key IDs--- ;
left_id := 1001
right_id := 1002
up_id := 1003
down_id := 1004
jump_id := 1005
run_id := 1006
inventory_id := 1007
confirm_id := 1008
cancel_id := 1009
escape_id := 1010
chat_id := 1011
tab_id := 1012
debug_id := 1013

; ---Code--- ;

init := DllCall(dll . "\" . INIT)
if (init != 0)
	DllCall(dll . "\" . EH, "Int", init)

dll_result(key_id) {
	result := DllCall(dll . "\" . TCPT, "Int", tcp, "Int", key_id)
	if (result != 0)
		DllCall(dll . "\" . EH, "Int", result)
	Return
}

; ---Keybinds--- ;

Left::dll_result(left_id)
Right::dll_result(right_id)
Up::dll_result(up_id)
Down::dll_result(down_id)
Space::dll_result(jump_id)
Shift::dll_result(run_id)

C::dll_result(inventory_id)
Z::dll_result(confirm_id)
X::dll_result(cancel_id)
Esc::dll_result(escape_id)
T::dll_result(chat_id)
F12::dll_result(debug_id)
Tab::dll_result(tab_id)

Left UP::dll_result(left_id * 2)
Right UP::dll_result(right_id * 2)
Up UP::dll_result(up_id * 2)
Down UP::dll_result(down_id * 2)
Shift UP::dll_result(run_id * 2)
Tab UP::dll_result(tab_id * 2)
