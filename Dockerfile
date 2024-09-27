FROM niten01/arch-cpp:latest

WORKDIR /app

COPY . .

RUN mkdir -p build-res

# debug clang
RUN cmake -S . \
			-B build-tmp \
			-G Ninja \
			-DCMAKE_CXX_COMPILER=clang++ \
			-DCMAKE_C_COMPILER=clang \
			-DCMAKE_BUILD_TYPE=Debug && \
			cmake --build build-tmp --parallel $(nproc) && \
			mv build-tmp/wordly build-res/wordly-clang-debug && rm -rf build-tmp

# release clang
RUN cmake -S . \
			-B build-tmp \
			-G Ninja \
			-DCMAKE_CXX_COMPILER=clang++ \
			-DCMAKE_C_COMPILER=clang \
			-DCMAKE_BUILD_TYPE=Release && \
			cmake --build build-tmp --parallel $(nproc) && \
			mv build-tmp/wordly build-res/wordly-clang-release && rm -rf build-tmp

# debug gcc
RUN cmake -S . \
			-B build-tmp \
			-G Ninja \
			-DCMAKE_CXX_COMPILER=g++ \
			-DCMAKE_C_COMPILER=gcc \
			-DCMAKE_BUILD_TYPE=Debug && \
			cmake --build build-tmp --parallel $(nproc) && \
			mv build-tmp/wordly build-res/wordly-gcc-debug && rm -rf build-tmp

# release gcc
RUN cmake -S . \
			-B build-tmp \
			-G Ninja \
			-DCMAKE_CXX_COMPILER=g++ \
			-DCMAKE_C_COMPILER=gcc \
			-DCMAKE_BUILD_TYPE=Release && \
			cmake --build build-tmp --parallel $(nproc) && \
			mv build-tmp/wordly build-res/wordly-gcc-release && rm -rf build-tmp

CMD cp --remove-destination build-res/* build
