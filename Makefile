image:
	cd resources && sudo docker build -t yall:latest .

build:
	sudo docker run -it -e "DEPLOY=false" -e "SONAR_KEY=f9cdfa9f00fc40dede499826b93a3f388f54f789" -v `pwd`:/yall --name yall yall:latest
	sudo docker cp yall:/build/packages ./
	sudo docker stop yall && sudo docker rm yall

.PHONY: image build