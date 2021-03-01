// const USERNAME = 'postgres'
// const PASSWORD = 'd152535k'
// const HOST = 'localhost'
// const PORT = 5432
// const DB_NAME = 'dbSapHasap'
// const DIALECT = 'postgresql'

// const USERNAME = 'sa'
// const PASSWORD = '123456'
// const HOST = '192.168.0.10'
// const PORT = 1433
// const DB_NAME = '25.02.2021'
// const DIALECT = 'mssql'

const db = 'mssql'

postgresql_config = {
	USERNAME: 'postgres',
	PASSWORD: 'd152535k',
	HOST: 'localhost',
	PORT: 5432,
	DB_NAME: 'dbSapHasap',
	DIALECT: 'postgresql',
}


mssql_config = {
	USERNAME: 'sa',
	PASSWORD: '123456',
	HOST: '192.168.0.10',
	PORT: 1433,
	DB_NAME: '25.02.2021',
	DIALECT: 'mssql',
}

if (db == 'mssql') {
	module.exports = mssql_config	
}

else {
	module.exports = postgresql_config
}

// module.exports = {
// 	USERNAME: USERNAME,
// 	PASSWORD: PASSWORD,
// 	HOST: HOST,
// 	PORT: PORT,
// 	DB_NAME: DB_NAME,
// 	DIALECT: DIALECT
// }