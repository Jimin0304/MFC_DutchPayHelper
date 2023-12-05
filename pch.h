// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"
#include <mysql.h>
#include <WinSock2.h>

#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "ws2_32.lib")

#define CON_IP "localhost"			// 호스트 IP
#define DB_USER "root"				// 접속 ID
#define DB_PASS "qwer1234"			// 접속 암호
#define DB_NAME "dutchpayhelper"	// DB명

#define SQL_CREATE_SETTLEMENT_TABLE "CREATE TABLE settlement (\
	seq INT NOT NULL AUTO_INCREMENT,\
	settlement_date     Date,\
	settlement_name VARCHAR(50),\
	general_affairs VARCHAR(20),\
	account_num VARCHAR(50),\
	memo VARCHAR(100),\
	is_completed     bool,\
	amount_unit VARCHAR(5),\
	PRIMARY KEY(seq)\
	) ENGINE = MYISAM CHARSET = utf8mb4; "
#define SQL_CREATE_CONTENT_TABLE "CREATE TABLE content (\
	content_seq INT NOT NULL AUTO_INCREMENT,\
	settlement_seq INT,\
	degree VARCHAR(5),\
	amount Long,\
	place  VARCHAR(50),\
	PRIMARY KEY(content_seq),\
	FOREIGN KEY(settlement_seq) REFERENCES settlement(seq)\
	) ENGINE = MYISAM CHARSET = utf8mb4;"
#define SQL_CREATE_PARTICIPANTS_TABLE "CREATE TABLE participants (\
	participants_seq INT NOT NULL AUTO_INCREMENT,\
	content_seq INT NOT NULL,\
	name VARCHAR(20),\
	paid bool,\
	money_to_pay Long,\
	PRIMARY KEY(participants_seq),\
	FOREIGN KEY(content_seq) REFERENCES content(content_seq)\
	) ENGINE = MYISAM CHARSET = utf8mb4; "

extern MYSQL Connect;
extern MYSQL_RES* sql_result;
extern MYSQL_ROW sql_row;

#endif //PCH_H
