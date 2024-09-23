#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	// 0 Argument
	if (argc <= 1) {
		errno = EINVAL;
		perror("ERROR: No arguments provided");
		exit(errno);
	}

	// Single program
	if (argc == 2) {
		if (execlp(argv[1], argv[1], NULL) == -1) {
			perror("ERROR: Failed to execute the single program inputted.");
			exit(errno);
		}
		return 0;
	}

	// 2 or more programs
	if (argc >= 3) {
		// Two pipes
		int curr_pipe[2];
		int prev_pipe[2];

		for (int i = 1; i < argc; i++) {
			// A pipe is created only if it is not the last program.
			if (i < argc - 1) {
				if (pipe(curr_pipe) == -1) {
                    perror("ERROR: Pipe creation failed");
                    exit(errno);
                }
			}

			// Create a child process
			int pid = fork();

			if (pid < 0) {
				perror("ERROR: Fork failed.");
				exit(errno);
			}

			// Child process behavior
			if (pid == 0) {
				// If it is not the first program, redirect the previous pipe's read end to stdin.
				if (i > 1) {
					if (dup2(prev_pipe[0], STDIN_FILENO) == -1) {
                        perror("ERROR: dup2 for stdin failed");
                        exit(errno);
                    }
					close(prev_pipe[0]);
                    close(prev_pipe[1]);
				}

				// If it is not the last program, redirect the current pipe's wirte end to stdout.
				if (i < argc - 1) {
					if (dup2(curr_pipe[1], STDOUT_FILENO) == -1) {
                        perror("ERROR: dup2 for stdout failed");
                        exit(errno);
                    }
					close(curr_pipe[0]);
					close(curr_pipe[1]);
				}

				if (execlp(argv[i], argv[i], NULL) == -1) {
					perror("ERROR: Failed to execute program within child process");
					exit(errno);
				}
				
				return 0;
				
			} else { 
				// Parent process behavior
				// Close previous pipes in the parent process
                if (i > 1) {
                    close(prev_pipe[0]);
                    close(prev_pipe[1]);
                }

                // If it is not the last command, update previous pipe.
                if (i < argc - 1) {
                    prev_pipe[0] = curr_pipe[0];
                    prev_pipe[1] = curr_pipe[1];
                }

                // Wait for the child process to finish
                int status;
                if (waitpid(pid, &status, 0) == -1) {
                    perror("ERROR: waitpid failed");
                    exit(errno);
                }

                // Check if child exited with an error
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                    return WEXITSTATUS(status);
                }
			}
		}
	}

	return 0;
}