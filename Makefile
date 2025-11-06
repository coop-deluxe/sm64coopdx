# minimal example: run codegen as a pre-build step
GEN_DIR := generated
MAP := config/address_map.json
REGION ?= US

$(GEN_DIR)/rom_offsets.c $(GEN_DIR)/rom_offsets.h: $(MAP)
	mkdir -p $(GEN_DIR)
	python3 tools/codegen.py --map $(MAP) --region $(REGION) --out-dir $(GEN_DIR)

all: $(GEN_DIR)/rom_offsets.c
	@echo "Build would continue here. Ensure you add $(GEN_DIR)/rom_offsets.c to your build sources."