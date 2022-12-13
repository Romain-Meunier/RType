#!/bin/bash

apt install pip
echo "instalation et config de conan"
pip install conan
sleep 2
echo "test de la commande conan"
conan
sleep 2
echo "config des remote conan"
conan remote add conancenter https://center.conan.io/
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
echo "check remost list"
conan remote list