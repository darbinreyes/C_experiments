CC = cc
PROB_NAME = hacker_rank_median_updates
SOURCE_FILES = main_median_updates.c median_updates.c
OUT_EXE = $(PROB_NAME).bin

all:
  $(CC) -o $(OUT_EXE) -lpthread $(SOURCE_FILES)
  # make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

build:
  $(CC) -o $(OUT_EXE) -lpthread $(SOURCE_FILES)

clean:
  rm $(OUT_EXE)
  # make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
run:
  ./$(OUT_EXE)