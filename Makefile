CALLER_ID = Make
RUN_CMD = platformio --force --caller $(CALLER_ID) run

make:
	$(RUN_CMD)

clean:
	$(RUN_CMD) --target clean


upload:
	$(RUN_CMD) --target upload

monitor:
	platformio device monitor --baud 115200

