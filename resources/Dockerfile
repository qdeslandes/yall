# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

FROM debian:stretch

RUN apt-get update
RUN apt-get install -y wget build-essential git python3 valgrind rpm unzip openjdk-8-jdk

# Install CMake (recent version)
RUN wget https://cmake.org/files/v3.10/cmake-3.10.0-Linux-x86_64.sh -O cmake.sh && \
	chmod +x cmake.sh && \
	./cmake.sh --skip-license

# Install Criterion
RUN git clone --recursive -j8 https://github.com/Snaipe/Criterion.git && \
	cd Criterion && \
	cmake . && \
	make -j 9 && \
	make install

# Install SonarQube scanner. The scanner is launched a first time to fill cache
RUN wget https://sonarsource.bintray.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-3.0.3.778-linux.zip && \
	unzip sonar-scanner-cli-3.0.3.778-linux.zip && rm sonar-scanner-cli-3.0.3.778-linux.zip && \
	/sonar-scanner-3.0.3.778-linux/bin/sonar-scanner -Dsonar.host.url=https://sonarcloud.io || true && \
	wget https://sonarsource.bintray.com/CommercialDistribution/sonar-cpp-plugin/build-wrapper-3.10.zip && \
	unzip build-wrapper-3.10.zip && rm build-wrapper-3.10.zip

WORKDIR /build

CMD \
	cmake -DCMAKE_BUILD_TYPE=Release /yall && \
	/build-wrapper-3.10/linux-x86-64/build-wrapper-linux-x86-64 --out-dir bw_output make -j 9 clean all && \
	make validate && \
	make package && \
	if [ "$DEPLOY" = true ]; then \
		cmake -DCMAKE_BUILD_TYPE=Debug /yall && make -j 9 package && \
		/sonar-scanner-3.0.3.778-linux/bin/sonar-scanner \
			-Dsonar.cfamily.build-wrapper-output=/build/bw_output \
			-Dproject.settings=/yall/.sonar-project.properties \
			-Dsonar.projectBaseDir=/yall \
			-Dsonar.cfamily.gcov.reportsPath=/build/coverage \
			-Dsonar.projectVersion=`cat /build/yall.version` \
			-Dsonar.login=$SONAR_KEY; \
	else \
		/sonar-scanner-3.0.3.778-linux/bin/sonar-scanner \
			-Dsonar.cfamily.build-wrapper-output=/build/bw_output \
			-Dproject.settings=/yall/.sonar-project.properties \
			-Dsonar.projectBaseDir=/yall \
			-Dsonar.cfamily.gcov.reportsPath=/build/coverage \
			-Dsonar.projectVersion=`cat /build/yall.version` \
			-Dsonar.login=$SONAR_KEY \
			-Dsonar.analysis.mode=preview \
			-Dsonar.github.oauth=$GITHUB_KEY \
			-Dsonar.github.repository=Naccyde/yall \
			-Dsonar.github.pullRequest=$GITHUB_PR -X; \
	fi
