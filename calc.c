
//calc.c
 #include"App.h"
#include<stdio.h>
#include<dlfcn.h>//dynamic loading funs  
 //extern int countTotal(int[],int);

JNIEXPORT jint JNICALL Java_App_calcBill(JNIEnv *env, jclass jobj, jintArray arr) 
{
 int i ,sum =0;
 jsize len = (*env)->GetArrayLength(env, arr) ;
 void *p=NULL;
 int (*countTotal)(int[],int)=NULL;//fun ptr counter
 jint *params =(*env)->GetIntArrayElements( env,arr,0);
 p=dlopen("/home/dell/Desktop/CompShoppiProj/calclogic.so",RTLD_LAZY); 
  
 if (!p)
{
 printf("Unable to load library :%s\n",dlerror());
}
countTotal= dlsym(p,"countTotal");//define fun address (sym-symbol)

if (countTotal==NULL)
{
 printf(" Unable to get address of funtion :%s\n",dlerror());
}

sum=countTotal(params,len);

(*env)->ReleaseIntArrayElements(env,arr,params,0);
dlclose(p);
return sum ;
}
 


