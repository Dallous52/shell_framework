include config.mk

all:

	#遍历地编译每一个需要编译的文件夹
	@for dir in $(BUILD_DIR);\
	do\
		make -C $$dir;\
	done


clean:
	
	rm -rf log/link_obj log/dep
	rm -rf log/*.ghc	
