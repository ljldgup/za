from datetime import date, datetime
from pyspark import SparkContext, SparkConf
from pyspark.sql import SparkSession
from pyspark.sql.functions import udf, array_contains, col
from pyspark.sql.pandas.functions import pandas_udf, PandasUDFType
from pyspark.sql.types import StructField, StringType, ArrayType, DateType, TimestampType

'''
处理e6 文件信息
主要是通过udf 增加列和pandas_udf聚合
mapReduce的操作思想比较重要
传统的顺序操作，比较适合将数据集缩小后使用pandas等进行
'''

appName = 'fms_log_test'

spark = SparkSession \
    .builder \
    .appName("appName") \
    .getOrCreate()
sc = spark.sparkContext


############################################################
# 将日志信息转化位表中一行
def log_to_row(line):
    if 'starting' in line:
        attr0 = line.split(' ----- ')
        return attr0[0], -1, -1, 'start', attr0[1]

    attr0 = line.split(' : ')
    attr1 = attr0[0].split('/')
    # 时间，线程，操作，日志等及, 具体日志
    # attr1[6]具体日志，在实际操作中应该变为类型
    return attr1[0], int(attr1[1]), int(attr1[2]), attr1[3], attr0[1]


# 读取文件转表
lines = sc.textFile("/ljl/fms/fms_log.txt")

# 去掉空行 以及特殊信息
info = lines.filter(lambda line: ' : ' in line or ' ----- ' in line).map(log_to_row)

df = spark.createDataFrame(
    info, "date_str string, thread_num int, operation int, level string, context string")


#####################################################################
# 对日志内容进行编码，目前未使用，发现fp growth不用编码也可以使用
def context_process(x):
    return x.split(' ')[0]


# dataframe的映射需要用withColumn或select + udf,select 需要重命名
context_process = udf(context_process, StringType())
df = df.withColumn('one_context', context_process(df['context']))


####################################################

# 字符串转时间
def str_2_date(x):
    return datetime.strptime(x, "%a %b %d %H:%M:%S %Y")


# 时间转月日分钟字符串，用于groupby统计
def date_2_min(x):
    return x.strftime("%b %d %H")


# dataframe的映射需要用withColumn或select + udf,select 需要重命名相当于rdd中的map
# TimestampType 能保留时分秒 ， DateType 会被转成 date类型
str_2_date = udf(str_2_date, TimestampType())
date_2_min = udf(date_2_min, StringType())

df = df.withColumn('date', str_2_date(df['date_str']))
# 这里发现str_2_date 输入已经是datetime 可能spark 进行了处理
df = df.withColumn('min_str', date_2_min(df['date']))

# 每分钟新开资源统计
df.filter(df['one_context'].startswith('Begin')).groupby(df['min_str']).count().show(10, False)


