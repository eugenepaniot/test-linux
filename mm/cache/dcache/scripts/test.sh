#!/bin/bash

# 创建文件
test_create_file()
{
	mkdir -p ./test.out
	cd ./test.out

	i=0
	while (( i < 100000 )) ; do
	  if test -e ./$i; then
		# d_alloc() here
		echo $i > ./$i
	  fi
	  ((i++))
	done

	cd ..

	rm -rf ./test.out
}

# 创建文件夹
test_create_dir()
{
	mkdir -p ./test.out
	cd ./test.out

	i=0
	while (( i < 100000 )) ; do
	  if test -e ./$i; then
		# d_alloc() here
		mkdir $i
	  fi
	  ((i++))
	done

	cd ..

	rm -rf ./test.out
}

#test_create_file
#test_create_dir

