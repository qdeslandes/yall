image:
	cd resources && sudo docker build -t yall:latest .

build:
	sudo docker cp yall:/build/packages ./
	sudo docker stop yall && sudo docker rm yall

.PHONY: image build