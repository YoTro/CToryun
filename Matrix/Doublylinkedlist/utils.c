#include "utils.h"

int count_fields(char *line){
	int count = 0;
	int i = 0;
	char c = ',';
	while(line[i] != '\0'){
		if (c == line[i])
		{
			++count;
		}
		
		i++;
	}
	if (i > 1)
	{
		count++;
	}
	return count;
}
/*把行中数字提取到数组并返回
c: 字符指针
num: 数字指针
end: 行中非数字字符串指针
done: 是否结束(1:结束, 0:没有)
*/
float *parse_fields(char *line, int cols){
	
	float *field = calloc(cols, sizeof(float));
	
	char *c, *num, *end;
	int done = 0, i = 0;
	for(c = line, num = line;!done;++c){
		done = (*c == '\0'); //(0: 不相等没到结尾, 1: 相等到达字符串末尾)
		if (*c == ',' || done)
		{
			*c = '\0'; 
			field[i] = strtod(num, &end);//读取字符串中的数字,跳过开头的空格符直到不能转换成数字的字符为止的数字字符,然后转换成浮点数, end 返回不能转换成数字的字符串. 没有数字则返回0, 溢出返回HUGE_VAL, HUGE_VALF, or HUGE_VALL
			if (num == c)
			{
				field[i] = nan("");//BSD Library Functions Manual, return a quiet NaN
			}

			if (end != c && (end != c - 1 || *end != 'r'))//CR = Carriage Return，回车符号（\r，十六进制 ascii 码为0x0D，十进制 ascii 码为13），用于将鼠标移动到行首，并不前进至下一行。https://developer.mozilla.org/zh-CN/docs/Glossary/CRLF
			{
				field[i] = nan("");
			}
			num = c + 1;
			i++;

		}
	}
	return field;
}

char *fgetl(FILE *fp){
	if (feof(fp))
	{
		return 0;//check and reset stream status, 如果文件流结束则返回非零值
	}
	
	size_t size = 512; 
	char *line = malloc(size*sizeof(char));
	if (!fgets(line, size, fp))//get a line from a stream reads at most one less than the number of characters specified by size from the given stream and stores them in the string str. return if any ? NULL : a pointer to the string
	{
		free(line);
		return 0;
	}
	//在上述判断fgets()中, line已经被指向从fp读取的一行字符串首地址了, 所以curr为当前行字符串大小
	size_t curr = strlen(line);
	//读取的行若大小超过size且没有读完,则扩充并继续读取
	while(!feof(fp) && (line[curr-1] != '\n')){
		if(curr == size - 1){
			size *= 2;
			line = realloc(line, size*sizeof(char));//在原来的基础上扩展两倍, 但是指针地址改变
			if (!line)
			{
				//超过系统类型大小限制, 分配不了内存, 显示size大小
				printf("%ld\n", size);
				fprintf(stderr, "Malloc error\n");
				exit(-1);
			}
		}
		size_t readsize = size - curr;
		if (readsize > INT_MAX)
		{
			readsize = INT_MAX - 1;
		}
		fgets(&line[curr], readsize, fp); //接着读取未读完的字符串直到'\n'或'\0'
		curr = strlen(line);
	}
	if (line[curr - 1] == '\n')
	{
		line[curr - 1] = '\0';//换行结束
	}
	return line;
}
