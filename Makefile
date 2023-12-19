all:
	@clear
	@g++ *.cpp -std=c++11 -o ext_4_estrutura
	@./ext_4_estrutura images_ext4/myext4image2k.img
	@rm ext_4_estrutura

compile:
	@g++ *.cpp -std=c++11 -o ext_4_estrutura

exec4k:
	@./ext_4_estrutura images_ext4/myext4image4k.img

exec2k:
	@./ext_4_estrutura images_ext4/myext4image2k.img

exec1k:
	@./ext_4_estrutura images_ext4/myext4image1k.img

delete:
	@rm ext_4_estrutura