# compile and (by default) run - then (by default) clean 

perform_compilation=1
perform_run=1
perform_clean=1

while [ $# -gt 0 ]
do
    case "$1" in
        -h)
            echo "run.sh by KK"
            echo "==========================================================================="
            echo "to run siply do ./run.sh - it will perform compilation, run and cleanup"
            echo "if you want to disable some step just put according option:"
            echo "-ncmp - to disable compilation"
            echo "-nr   - to disable run"
            echo "-nc   - to disable cleanup"
            echo "==========================================================================="
            perform_compilation=0
            perform_run=0
            perform_clean=0
            ;;
        -ncmp)
            perform_compilation=0
            ;;
        -nr)
            perform_run=0
            ;;
        -nc)
            perform_clean=0
            ;;
        -*) echo "bad option $1!\n"
            ;;
    esac
    shift
done

if [ $perform_compilation -eq 1 ]; then
    gcc -o main fir.c main.c
fi

if [ $perform_run -eq 1 ]; then
    ./main
fi

if [ $perform_clean -eq 1 ]; then
    rm main
fi