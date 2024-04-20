

int checkCommand(char command[]){
  // QQ
  if(command[0] == 'Q' && command[1] == 'Q'){
    exit(0);
  }

  if(command[0] == '\0'){
    return -2;
  }

  // LD
  if(command[0] == 'L' && command[1] == 'D'){
    if(command[2] == '\0'){
        return 0;
    }
    return 1;
  }

  // SW
  if(command[0] == 'S' && command[1] == 'W'){
    return 2;
  }


  // SL
  if(command[0] == 'S' && command[1] == 'I' && command[2] == '\0'){
    return 3;
  }

  if(command[0] == 'S' && command[1] == 'I' && command[2] == ' ' && command[3] >= '0' && command[3] <= '9' && command[4] == '\0'){
    return 4;
  }

  if(command[0] == 'S' && command[1] == 'I' && command[2] == ' ' && command[3] >= '0' && command[4] >= '0' && command[4] <= '9' && command[5] == '\0'){
    return 5;
  }

  //SR
  if(command[0] == 'S' && command[1] == 'R' && command[2] == '\0'){
    return 6;
  }

  if(command[0] == 'S' && command[1] == 'D'){
    return 8;
  }

  if(command[0] == 'P' && command[1] == '\0'){
    return 7;
  }




  return -1;

}
