% Carrega e limpa os dados
dados = load('data\data_199.txt');
dados = dados(all(~isnan(dados), 2), :);
A_init = dados(:,1);
V_init = dados(:,2);
t_init = dados(:,3) / 1000;

n_total = length(V_init);
n_amostras = 5000;

indices = round(linspace(1, n_total, n_amostras));
V = V_init(indices);
A = A_init(indices);
t = t_init(indices);
% Suavização do sinal de tensão
V_suave = movmean(V, 50);  % Janela ajustável

V_suave1 = movmean(V, 5);  % Janela ajustável
A_suave1 = movmean(A, 5);  % Janela ajustável

% Derivadas
dt = mean(diff(t));
dV_dt_raw = gradient(V_suave, dt);          % Primeira derivada bruta
dV_dt = movmean(dV_dt_raw, 100);             % Suaviza a primeira derivada
d2V_dt2 = gradient(dV_dt, dt);              % Segunda derivada

% Encontra extremos com base na segunda derivada suavizada
[picos_pos, idx_max] = findpeaks(d2V_dt2, 'MinPeakProminence', 7*std(d2V_dt2), 'MinPeakDistance', 300);
[picos_neg, idx_min] = findpeaks(-d2V_dt2, 'MinPeakProminence', 6*std(d2V_dt2), 'MinPeakDistance', 300);

% Junta e ordena
extremosIdx = sort([idx_max; idx_min]);
if mod(length(extremosIdx), 2) ~= 0
    extremosIdx(end) = [];
end

% Visualização das derivadas


% Identifica os últimos dois mínimos e o último máximo
if length(idx_min) >= 2 && length(idx_max) >= 1
    % Últimos dois mínimos (vales) e último máximo (pico)
    idx_min_finais = sort(idx_min(end-1:end));  % dois últimos mínimos ordenados
    idx_max_final = idx_max(find(idx_max > idx_min_finais(1) & idx_max < idx_min_finais(2), 1, 'last'));

    if ~isempty(idx_max_final)
        idx_ini = idx_min_finais(1);
        idx_meio = idx_max_final;
        idx_fim = idx_min_finais(2);

        % Plota apenas esse ciclo triangular
        figure;

        hold on;
        
       subplot(3,1,1);
        plot(t, V,'LineWidth', 0.5); title('Tensão (V)');
        ylabel('Tensão (V)');
        xlabel('Tempo (s)');
        ylim([-0.1 2.1]);
        %xlim([0 1200]);
        grid on;

        subplot(3,1,2);
        plot(t, A,'LineWidth', 0.5);
        title('Corrente (mA)');
        ylabel('Corrente (mA)');
        xlabel('Tempo (s)');
        grid on;
        ylim([-0.7 0.7]);
        %xlim([0 1200]);

        subplot(3,1,3);
        V_ciclo = V(idx_ini:idx_fim);
        A_ciclo = A(idx_ini:idx_fim);
        plot(V_ciclo, A_ciclo, 'b-', 'LineWidth', 0.5);
        xlim([-0.1 2.1]);
        ylim([-0.7 0.7]);
        xlabel('Tensão (V)');
        ylabel('Corrente (mA)');
        grid on;
        title('Último ciclo triangular (voltamograma)');

    else
         figure;

        hold on;
       subplot(2,1,1);
        plot(t, V,'LineWidth', 0.5); title('Tensão (V)');
        ylabel('Tensão (V)');
        xlabel('Tempo (s)');
        ylim([-0.1 5.1]);
        %xlim([0 1200]);
        grid on;

        subplot(2,1,2);
        plot(t, A*100,'LineWidth', 0.5);
        title('Corrente (mA)');
        ylabel('Corrente (mA)');
        xlabel('Tempo (s)');
        grid on;
        ylim([-60 60]);
        %xlim([0 1200]);
        warning('Nenhum máximo encontrado entre os dois últimos mínimos.');
    end
else
    warning('Número insuficiente de mínimos ou máximos para formar um ciclo completo.');
end
figure;
hold on;
        
       subplot(3,1,1);
        plot(t, V,'LineWidth', 0.5); title('Tensão (V)');
        ylabel('Tensão (V)');
        xlabel('Tempo (s)');
        ylim([-0.1 5.1]);
        %xlim([0 1200]);
        grid on;

        subplot(3,1,2);
        plot(t, A,'LineWidth', 0.5);
        title('Corrente (mA)');
        ylabel('Corrente (mA)');
        xlabel('Tempo (s)');
        grid on;
        ylim([-0.20 0.20]);
        %xlim([0 1200
subplot(3,1,3);
        V_ciclo = V(idx_ini:idx_fim);
        A_ciclo = A(idx_ini:idx_fim);
        plot(V_ciclo, A_ciclo, 'b-', 'LineWidth', 0.5);
        xlim([-0.1 2.1]);
        ylim([-0.7 0.7]);
        xlabel('Tensão (V)');
        ylabel('Corrente (mA)');
        grid on;
        title('Último ciclo triangular (voltamograma)');