NAME := sql_lite_clone
OS := $(shell uname)
TAG := $(shell git log -1 --pretty=%h)
IMG := ${NAME}:${TAG}
LATEST := ${NAME}:latest
CONAN_PROFILE := default

documentation:
	rm -rf docs/* latex/*
	doxygen Doxyfile

cleanData:
	rm -rf data/*

cleanCmake:
	rm -rf cmake-build/*

installDeps:
	cd build && conan install .. --profile ${CONAN_PROFILE} && bundle binstubs --all

buildImage:
	docker build -t ${IMG} .
	docker tag ${IMG} ${LATEST}

buildDb:
	(mkdir cmake-build || echo "cmake exists") && cd cmake-build && cmake .. && make

runDb: cleanCmake installDeps buildDb
	./cmake-build/src/sqlLiteClone

tests: cleanCmake installDeps buildDb
	rspec

in_docker: buildImage ## Run like so: `make in_docker TARGET=tests`
	docker run --user=root -v $(PWD):/app --rm ${IMG} make $(TARGET)

compose_bash:
	docker-compose run --rm db /bin/bash