# Setting up gem5 and DRFQS for Linux

# Compilation of gem5

1. Clone this repository
2. Initialize submodules 
		```
			git submodule update --init --recursive
		```
3. Install venv and python 2.7, according to https://stackoverflow.com/questions/61879640/gem5-scons-build-fails-with-typeerror-argument-should-be-integer-or-bytes-like

		```
		sudo apt-get install virtualenv
		# create a virtualenv which uses python 2.7
		virtualenv -p python2.7 venv27
		# activate the virtualenv
		. venv27/bin/activate
		# Install SCons in the python 2.7 virtualenv
		pip install scons
		# This will now use the scons installed in a python 2.7 virtualenv.
		scons build/X86/gem5.opt -j8
		```
4. Build gem5 following https://docs.simplessd.org/en/v2.0.12/instructions/start.html

5. You can switch to branch ``original`` and build to run gem5 without DRFQS.

# Compilation of Linux Kernel
1. Clone repository https://github.com/captgao/linux-bfs-drfq
2. Follow the tutorial from SimpleSSD to build the kernel with configuration for gem5 https://docs.simplessd.org/en/v2.0.12/tips/kernel.html.
3. Download the rootfs image from https://drive.google.com/file/d/1mAUaU2yVFKNNhSFAbghpWYKWt0opUYKam, replace the line ``DiskImageFile1`` in ``<GEM5_REPO>/src/dev/storage/simplessd/config/linaro.cfg`` with your path to te image file.
4. You can use original Linux kernel in step 2 to run Linux without DRFQS.

# Running Experiments
1. Run gem5 using the following command
		```
		./build/ARM/gem5.fast ./configs/example/fs.py --fast-forward=500000000 --kernel=vmlinux --dtb-file=armv8_gem5_v1_4cpu.dtb --machine-type=VExpress_GEM5_V1 --num-cpu=4 --cpu-clock=3GHz --caches --l2cache --cpu-type=TimingSimpleCPU --mem-size=4GB --mem-type=LPDDR2_S4_1066_1x32 --ssd-interface=nvme --ssd-config=./src/dev/storage/simplessd/config/linaro.cfg --disk-image=linaro-aarch64-linux.img --root-device=/dev/nvme0n1p1 --disable-ide
		```
2. ``fio`` benchmark is provided in the image in home directory. You can add other benchmarks and applications by mounting the rootfs image.

