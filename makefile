include config.mk

all:

	#�����ر���ÿһ����Ҫ������ļ���
	@for dir in $(BUILD_DIR);\
	do\
		make -C $$dir;\
	done


clean:
	
	rm -rf log/link_obj log/dep
	rm -rf log/*.ghc	
