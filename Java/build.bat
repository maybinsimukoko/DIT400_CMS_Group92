@echo off
echo Compiling Java program...
javac Main.java
if %errorlevel%==0 (
    echo Creating executable JAR...
    jar cfe cms_java.jar Main Main.class
    echo Build complete! Run java -jar cms_java.jar
) else (
    echo Compilation failed!
)
pause
