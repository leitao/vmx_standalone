set confirm off
layout split

define args
  i r r3 r4 r5 r6 r7
end

define fp
	x/32gx $r1
end

define encrypt
	break aes_p8_encrypt
	break aes_p8_decrypt
	run
	set $src = $r3
	set $dst = $r4
	set $enc = $r5
	i r r3 r4 r5
end

define default
	break main:36
	break aes_p8_set_encrypt_key
	break aes_p8_set_decrypt_key
	break aes_p8_encrypt
	break aes_p8_decrypt
	break aesp8-ppc.S:135
	run
end
