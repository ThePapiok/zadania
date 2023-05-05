CREATE OR REPLACE TYPE matrix IS TABLE OF CLOB;
/

CREATE OR REPLACE TYPE pair_exists IS TABLE OF CLOB;
/

CREATE OR REPLACE TYPE type_graphlet IS VARRAY(13) OF INTEGER;
/

CREATE OR REPLACE TYPE degree IS VARRAY(10) OF INTEGER;
/

CREATE OR REPLACE PROCEDURE CREATE_MATRIX(array_matrix IN OUT matrix,selected_option VARCHAR2)
IS
    cur sys_refcursor;
    index_m INTEGER;
    value_table INTEGER;
    one_loop NUMBER(1):=0;
	TYPE temp IS TABLE OF VARCHAR(2);
	array_temp temp:=temp();
	name VARCHAR2(35);
	maxl INTEGER:=0;
	index1 INTEGER;
	index2 INTEGER;
BEGIN
	IF selected_option = 'a' THEN
		name:='MACIERZ_SASIEDZTWA';
	ELSE
		name:='LISTA_KRAWEDZI_I_LISTA_WIERZCHOLKOW';
	END IF;
	FOR c IN (SELECT column_name FROM all_tab_columns WHERE table_name = name)
	LOOP
		index_m:=1;
		OPEN cur FOR 'select ' || c.column_name || ' from ' || name;
		LOOP
			FETCH cur INTO value_table;
			EXIT WHEN cur%notfound;
			IF one_loop = 0 THEN
				IF selected_option = 'a' THEN
					array_matrix.EXTEND;
					array_matrix(index_m):=TO_CHAR(value_table);
				ELSE
					array_temp.EXTEND;
					maxl:=GREATEST(maxl,value_table);
					array_temp(index_m):=TO_CHAR(value_table);
				END IF;
			ELSE
				IF selected_option = 'a' THEN
					array_matrix(index_m):=array_matrix(index_m)||TO_CHAR(value_table);
				ELSE
					maxl:=GREATEST(maxl,value_table);
					array_temp(index_m):=array_temp(index_m)||TO_CHAR(value_table);					
				END IF;
			END IF;
			index_m:=index_m+1;
		END LOOP;
		CLOSE cur;
		one_loop:=1;
	END LOOP;
	IF selected_option = 'b' THEN
		FOR i IN 1..maxl
		LOOP
			array_matrix.EXTEND;
			array_matrix(i):=RPAD('0',maxl,'0');
		END LOOP;
		FOR i IN array_temp.FIRST..array_temp.LAST
		LOOP
			index1:=SUBSTR(array_temp(i),1,1);
			index2:=SUBSTR(array_temp(i),2,1);
			array_matrix(index1):=SUBSTR(array_matrix(index1),1,index2-1)||'1'||SUBSTR(array_matrix(index1),index2+1,maxl-index2);
		END LOOP;
	END IF;
END;
/

CREATE OR REPLACE PROCEDURE FIND(array_type_graphlet type_graphlet,array_matrix matrix,array_pair_exists IN OUT pair_exists,array_degree IN OUT degree,i INTEGER,j INTEGER,k INTEGER,i1 INTEGER,i2 INTEGER,v1 INTEGER, v2 INTEGER,v3 INTEGER,v4 INTEGER,l INTEGER)
IS
	vertex CLOB;
	sum_degree INTEGER;
	pair CLOB;
	array_index INTEGER;
	TYPE sorted IS TABLE OF INTEGER INDEX BY BINARY_INTEGER;
    array_sorted sorted;
	next_step NUMBER(1):=0;
BEGIN
	array_sorted(i):=0;
	array_sorted(j):=0;
	array_sorted(k):=0;
	array_index:=array_sorted.FIRST;
	LOOP
		pair:=pair||array_index;
		array_index:=array_sorted.NEXT(array_index);
		EXIT WHEN array_index IS NULL;
	END LOOP;
	array_index:=array_pair_exists.FIRST;
	LOOP
		EXIT WHEN array_index IS NULL;
		IF pair = array_pair_exists(array_index) THEN
			next_step:=1;
			EXIT;
		END IF;
		array_index:=array_pair_exists.NEXT(array_index);
	END LOOP;
	IF SUBSTR(array_matrix(k),i,1) = '1' AND next_step = 0 THEN
		array_degree(5):=v1;
		array_degree(6):=v2;
		array_degree(7):=array_degree(3);
		array_degree(8):=array_degree(4);
		array_degree(9):=v3;
		array_degree(10):=v4;
        IF SUBSTR(array_matrix(i),k,1) = '1' THEN
			array_degree(i1):=array_degree(i1)+1;
			array_degree(i2):=1;
        END IF;
        vertex:='';
        vertex:='('||j||','||i||','||k||')';
        IF SUBSTR(array_matrix(j),l,1) ='1' THEN
            array_degree(7):=array_degree(7)+1;
			array_degree(10):=array_degree(10)+1;
        END IF;
        IF SUBSTR(array_matrix(l),j,1) ='1' THEN
            array_degree(9):=array_degree(9)+1;
			array_degree(8):=array_degree(8)+1;
        END IF;
		array_pair_exists.EXTEND;
		array_pair_exists(array_pair_exists.LAST):=pair;
		sum_degree:=(array_degree(5)*10+array_degree(6))*(array_degree(7)*10+array_degree(8))*(array_degree(9)*10+array_degree(10));
		FOR p IN array_type_graphlet.FIRST..array_type_graphlet.LAST
		LOOP
			IF sum_degree = array_type_graphlet(p) THEN
				DBMS_OUTPUT.PUT_LINE('WIERZCHOLKI: '||vertex||'  TYP GRAFLETU: '||p);
				EXIT;
			END IF;
		END LOOP;
    END IF;
END;
/

CREATE OR REPLACE PROCEDURE FIND_GRAPHLETS(array_matrix matrix,array_pair_exists IN OUT pair_exists,array_degree IN OUT degree,array_type_graphlet type_graphlet)
AS
BEGIN
	array_degree.EXTEND(10);
    FOR i IN array_matrix.FIRST..array_matrix.LAST
    LOOP
        FOR j IN array_matrix.FIRST..array_matrix.LAST
        LOOP
            IF j<>i THEN
                IF SUBSTR(array_matrix(j),i,1) = '1' THEN
					array_degree(1):=0;
					array_degree(2):=1;
					array_degree(3):=1;
					array_degree(4):=0;
                    IF SUBSTR(array_matrix(i),j,1) = '1' THEN
						array_degree(1):=1;
						array_degree(4):=1;
                    END IF;
                    FOR k IN j+1..array_matrix.LAST
                    LOOP
                        IF k<>i THEN
                            FIND(array_type_graphlet,array_matrix,array_pair_exists,array_degree,i,j,k,5,10,array_degree(1),array_degree(2)+1,1,0,k);
                        END IF;
                    END LOOP;
                    FOR k IN 1..LENGTH(array_matrix(i))
                    LOOP
                        IF k<>j AND k<>i THEN
                            FIND(array_type_graphlet,array_matrix,array_pair_exists,array_degree,k,j,i,6,9,array_degree(1)+1,array_degree(2),0,1,k);
                        END IF;
                    END LOOP;
                END IF;
            END IF;
        END LOOP;
        FOR j IN 1..LENGTH(array_matrix(i))
        LOOP
            IF SUBSTR(array_matrix(i),j,1) = '1' AND j<>i THEN
				array_degree(1):=1;
			    array_degree(2):=0;
				array_degree(3):=0;
				array_degree(4):=1;
                IF SUBSTR(array_matrix(j),i,1) = '1' THEN
                    array_degree(3):=1;
					array_degree(2):=1;
                END IF;
                FOR k IN j+1..LENGTH(array_matrix(i))
                LOOP
					IF k<>i THEN
						FIND(array_type_graphlet,array_matrix,array_pair_exists,array_degree,k,j,i,6,9,array_degree(1)+1,array_degree(2),0,1,k);
					END IF;
                END LOOP;
            END IF;
        END LOOP;
    END LOOP;
END;
/

SET SERVEROUTPUT ON

ACCEPT x CHAR PROMPT 'a) - macierz sasiedztwa b) - lista krawedzi i lista wierzcholkow: '

DECLARE
    array_degree degree:=degree();
	array_type_graphlet type_graphlet:=type_graphlet(20,110,231,200,440,882,1320,2662,1331,2772,2880,5544,10648);
    array_matrix matrix:=matrix();
    array_pair_exists pair_exists:=pair_exists();
    selected_option VARCHAR2(1);
BEGIN
    selected_option:='&x';
    IF selected_option = 'a' THEN
        CREATE_MATRIX(array_matrix,selected_option);
    ELSIF selected_option = 'b' THEN
        CREATE_MATRIX(array_matrix,selected_option);
    ELSE 
        DBMS_OUTPUT.PUT_LINE('Ta opcja jest niedostepna!');
    END IF;
    IF selected_option = 'a' OR selected_option = 'b' THEN
        FIND_GRAPHLETS(array_matrix,array_pair_exists,array_degree,array_type_graphlet);
    END IF;
END;
/

DROP PROCEDURE CREATE_MATRIX;
DROP PROCEDURE FIND_GRAPHLETS;
DROP PROCEDURE FIND;
DROP TYPE matrix;
DROP TYPE pair_exists;
DROP TYPE type_graphlet;
DROP TYPE degree;