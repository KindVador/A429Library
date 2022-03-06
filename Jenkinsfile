pipeline {
    agent any

    options {
        checkoutToSubdirectory('A429Library')
    }

    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                sh 'if [ -d "build" ]; then rm -Rf build; fi'
                sh 'mkdir -p build'
                sh 'cmake -B build -S .'
                dir('build') {
                    sh 'make'
                }
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Documentation') {
            environment {
                DOXYOUTPUT = '/usr/share/nginx'
            }
            steps {
                echo 'Generating documentation..'
                dir('A429Library') {
                    sh 'rm -rf $DOXYOUTPUT/html'
                    sh 'doxygen'
                }
            }
        }
    }
}