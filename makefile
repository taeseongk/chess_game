CXX=clang++

chessGame: chessGame.o chessPiece.o chessBoard.o
	${CXX} chessGame.o chessPiece.o chessBoard.o -o chessGame

clean:
	/bin/rm -f *.o a.out